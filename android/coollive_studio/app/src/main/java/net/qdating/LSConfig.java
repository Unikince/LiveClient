package net.qdating;

/**
 * 推拉流模块初始化配置
 * @author max
 * @version 1.0.3
 */
public class LSConfig {
	final public static String VERSION = "1.0.4";
	/**
	 * 日志TAG
	 */
	public static String TAG = "coollive";
	/**
	 * 是否调试模式
	 */
	public static boolean debug = false;
	/**
	 * 重连时间
	 */
	public static Integer RECONNECT_SECOND = 3000;
	/**
	 * 初始化解码缓存(播放器参数)
	 * 总量 = 缓存时间 * FPS
	 */
	public static int VIDEO_DECODE_FRAME_COUNT = 30;
	/**
	 * 视频宽度(摄像头参数)
	 */
	public static int VIDEO_CAPTURE_WIDTH = 480;
	/**
	 * 视频高度(摄像头参数)
	 */
	public static int VIDEO_CAPTURE_HEIGHT = 640;
	/**
	 * 视频宽度(推流参数)
	 */
	public static int VIDEO_WIDTH = 240;
	/**
	 * 视频高度(推流参数)
	 */
	public static int VIDEO_HEIGHT = 240;
	/**
	 * 码率(推流参数)
	 */
	public static int VIDEO_BITRATE = 500 * 1000;
	/**
	 * 视频帧率(推流参数)
	 */
	public static int VIDEO_FPS = 12;
	/**
	 * 视频关键帧间隔(推流参数)
	 */
	public static int VIDEO_KEYFRAMEINTERVAL = VIDEO_FPS;
	/**
	 * 视频采集临时Buffer, 数值越大, 效率越高, 占用内存越大(推流参数)
	 */
	public static int VIDEO_CAPTURE_BUFFER_COUNT = 30 + VIDEO_FPS;
	/**
	 * 音频PCM采样率
	 */
	public static int SAMPLE_RATE = 44100;
	/**
	 * 音频PCM声道
	 */
	public static int CHANNEL_PER_FRAME = 1;
	/**
	 * 音频PCM精度
	 */
	public static int BIT_PER_SAMPLE = 16;
	
	/**
	 * 视频预览用的对象
	 */
	public static int MAGIC_TEXTURE_ID = 10;
	
	/**
	 * 渲染模式类型
	 * FillModeStretch 			满屏拉伸
	 * FillModeAspectRatioFit 	保持比例全图显示
	 * FillModeAspectRatioFill 	保持比例全屏显示
	 */
	static public enum FillMode {
		FillModeStretch, 
		FillModeAspectRatioFit,
		FillModeAspectRatioFill
	};
	
	/**
	 * 编解码模式
	 * @author max
	 * EncodeDecodeModeAuto 自动选择解码模式
	 * EncodeDecodeModeSoft 强制选择软解码模式
	 * EncodeDecodeModeHard 强制选择硬解码模式
	 */
	static public enum EncodeDecodeMode {
		EncodeDecodeModeAuto,
		EncodeDecodeModeSoft,
		EncodeDecodeModeHard
	}
	public static EncodeDecodeMode encodeDecodeMode = EncodeDecodeMode.EncodeDecodeModeAuto;
}