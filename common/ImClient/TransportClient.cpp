/*
 * author: Samson.Fan
 *   date: 2017-05-18
 *   file: TransportClient.cpp
 *   desc: 传输数据客户端接口类(负责与服务器之间的基础通讯，如Tcp、WebSocket等)
 */

#include "TransportClient.h"
#include <common/KLog.h>
#include <common/CommonFunc.h>
const long long WEBSOCKET_CONNECT_TIMEOUT = 30*1000;     // websoecket超时（毫秒）

TransportClient::TransportClient(void)
{
    m_connStateLock = IAutoLock::CreateAutoLock();
    m_connStateLock->Init();
    
    
    m_isInitMgr = false;
    
    m_connState = DISCONNECT;
    m_conn = NULL;
    m_isWebConnected = false;
    // 初始化websocket的锁
    mg_global_init();
}

TransportClient::~TransportClient(void)
{
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::~TransportClient() begin");

	// 释放mgr
	ReleaseMgrProc();
    // 释放websocket的锁
    mg_global_free();
    
    IAutoLock::ReleaseAutoLock(m_connStateLock);
    m_connStateLock = NULL;
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::~TransportClient() end");

}

// -- ITransportClient
// 初始化
bool TransportClient::Init(ITransportClientCallback* callback)
{
    m_callback = callback;
    return true;
}

// 连接
bool TransportClient::Connect(const char* url)
{
    bool result = false;
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::Connect() begin");
    m_isWebConnected = false;
    if (NULL != url && url[0] != '\0') {
        // 释放mgr,
        ReleaseMgrProc();
        m_connStateLock->Lock();
        if (DISCONNECT == m_connState) {
			// 创建mgr
            mg_mgr_init(&m_mgr, NULL);
            m_isInitMgr = true;
     
			// 连接url
            m_url = url;
            struct mg_connect_opts opt = {0};
            opt.user_data = (void*)this;
            m_conn = mg_connect_ws_opt(&m_mgr, ev_handler, opt, m_url.c_str(), "", NULL);
            //mg_set_timer(m_conn, mg_time() + 1.5);
            FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::Connect() m_conn:%p m_conn->err:%d m_conn->sock:%d start", m_conn, m_conn->err, m_conn->sock);
            if (NULL != m_conn && m_conn->err == 0) {
                m_connState = CONNECTING;
                result = true;
            }
        }
        m_connStateLock->Unlock();
        // 连接失败, 不放在m_connStateLock锁里面，因为mg_connect_ws_opt已经ev_handler了，导致ReleaseMgrProc关闭websocket回调ev_handler 的关闭 调用OnDisconnect的m_connStateLock锁
        if (!result) {
            if (NULL != m_conn) {
                // 释放mgr
                ReleaseMgrProc();
            }
            else {
                // 仅重置标志
                m_isInitMgr = false;
            }
        }

    }
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::Connect() end");
    return result;
}

// 断开连接
void TransportClient::Disconnect()
{
    m_connStateLock->Lock();
    DisconnectProc();
    m_connStateLock->Unlock();
}

// 断开连接处理(不锁)
void TransportClient::DisconnectProc()
{
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::DisconnectProc() m_conn:%p  m_connState:%d begin", m_conn, m_connState);
    // 当m_connState == CONNECTING时，im的socket还没有connect（可能是连socket都没有（因为ip为域名时mg_connect_ws_opt不去socket，都放到mg_mgr_poll去做，导致socketid没有，mg_shutdown 没有用，就设置DISCONNECT，使mg_mgr_poll结束））
    if (m_connState == CONNECTING || m_connState == DISCONNECT) {
        m_connState = DISCONNECT;
    }

    if (NULL != m_conn) {
        FileLog("ImClient", "TransportClient::DisconnectProc() m_conn:%p m_conn->err:%d m_conn->sock:%d m_connState:%d", m_conn, m_conn->err, m_conn->sock, m_connState);
        mg_shutdown(m_conn);
        m_conn = NULL;
    }
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::DisconnectProc() m_conn:%p  m_connState:%d end", m_conn, m_connState);
}

// 释放mgr
void TransportClient::ReleaseMgrProc()
{
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::ReleaseMgrProc(m_isInitMgr:%d) start", m_isInitMgr);
    if (m_isInitMgr) {
        mg_mgr_free(&m_mgr);
        m_isInitMgr = false;
    }
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::ReleaseMgrProc() end");
}

// 获取连接状态
ITransportClient::ConnectState TransportClient::GetConnectState()
{
    ConnectState state = DISCONNECT;
    
    m_connStateLock->Lock();
    state = m_connState;
    m_connStateLock->Unlock();
    return state;
}

// 发送数据
bool TransportClient::SendData(const unsigned char* data, size_t dataLen)
{
    
    bool result = false;
    if (NULL != data && dataLen > 0) {
        if (CONNECTED == m_connState && NULL != m_conn) {
             FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::SendData() m_conn:%p m_connState:%d  begin", m_conn, m_connState);
            mg_send_websocket_frame(m_conn, WEBSOCKET_OP_TEXT, data, dataLen);
           FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::SendData() m_conn:%p m_connState:%d  end", m_conn, m_connState);
			result = true;
        }
    }
    return result;
}

// 循环
void TransportClient::Loop()
{
    
     //Sleep(1000);
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::Loop() m_conn:%p m_connState:%d  begin", m_conn, m_connState);
    long long preTime = getCurrentTime();
    bool isOutTimeConnect = false;
    while (DISCONNECT != m_connState) {
        mg_mgr_poll(&m_mgr, 100);
        // 当websocket连接超过30秒就跳出（防止websocket无限连接，有时在ssl连接一只循环）
        if (m_connState == CONNECTING && DiffTime(preTime, getCurrentTime()) > WEBSOCKET_CONNECT_TIMEOUT) {
            isOutTimeConnect = true;
            break;
        }
    }

    if (!isOutTimeConnect) {
        // 如果im是连接中logout，没有走OnDisconnect，现在就走
        if (!m_isWebConnected) {
            FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::Loop() m_conn:%p m_connState:%d ", m_conn, m_connState);
            // 状态为已连接(返回断开连接)
            if (NULL != m_callback) {
                m_callback->OnDisconnect();
            }
        }
    } else {
        // 连接超时（websocket ssl连不上）
//        if (NULL != m_callback) {
//            m_callback->OnConnect(false);
//        }
        // 连接超时（websocket ssl连不上）,free websocket的管理器，会直接走到ev_handler 的 MG_EV_CLOSE
        FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::Loop() OutTimeConnect");
        ReleaseMgrProc();
    }
    
   Disconnect();

}


// -- mongoose处理函数
void TransportClient::ev_handler(struct mg_connection *nc, int ev, void *ev_data)
{
    struct websocket_message *wm = (struct websocket_message *) ev_data;
    TransportClient* client = (TransportClient*)nc->user_data;
   // FileLog("ImClient", "TransportClient::ev_handler(ev:%d)", ev);
    //FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::ev_handler(ev:%d)", ev);
    switch (ev) {
        case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
            // Connected
            client->OnConnect(true);
            //mg_set_timer(nc, 0);
            break;
        }
        case MG_EV_WEBSOCKET_FRAME: {
            // Receive Data
            client->OnRecvData(wm->data, wm->size);
            break;
        }
        case MG_EV_CLOSE: {
            // Disconnect
            client->OnDisconnect();
            break;
        }
       // case MG_EV_TIMER: {
        //    nc->flags |= MG_F_CLOSE_IMMEDIATELY;
        //    break;
        //}
    }
}

void TransportClient::OnConnect(bool success)
{
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::OnConnect(success :%d) start", success);
    // 连接成功(修改连接状态)
    if (success) {
        m_connState = CONNECTED;
        m_isWebConnected = true;
        // 返回连接成功(若连接失败，则在OnDisconnect统一返回)
        if (NULL != m_callback) {
            m_callback->OnConnect(true);
        }
    }
    
    // 连接失败(断开连接)
    if (!success) {
        Disconnect();
    }
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::OnConnect() end");
}

void TransportClient::OnDisconnect()
{
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::OnDisconnect() start");
    // 重置连接
    m_connStateLock->Lock();
    m_conn = NULL;
    m_connStateLock->Unlock();
    
    if (CONNECTED == m_connState) {
        // 状态为已连接(返回断开连接)
        if (NULL != m_callback) {
            m_callback->OnDisconnect();
            m_isWebConnected = false;
        }
    }
    else if (CONNECTING == m_connState || DISCONNECT == m_connState) {
        // 状态为连接中(返回连接失败)
        if (NULL != m_callback) {
            m_callback->OnConnect(false);
        }
    }
    
    // 修改状态为断开连接
    m_connState = DISCONNECT;
    FileLevelLog("ImClient", KLog::LOG_WARNING, "TransportClient::OnDisconnect() end");
}

void TransportClient::OnRecvData(const unsigned char* data, size_t dataLen)
{
    // 返回收到的数据
    if (NULL != m_callback) {
        m_callback->OnRecvData(data, dataLen);
    }
}
