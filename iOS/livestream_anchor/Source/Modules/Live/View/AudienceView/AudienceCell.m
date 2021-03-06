//
//  AudienceCell.m
//  livestream
//
//  Created by randy on 2017/8/30.
//  Copyright © 2017年 net.qdating. All rights reserved.
//

#import "AudienceCell.h"
#import "LSImageViewLoader.h"

@interface AudienceCell ()
@property (nonatomic, strong) LSImageViewLoader *imageLoader;
@end

@implementation AudienceCell

+ (NSString *)cellIdentifier {
    return @"AudienceCell";
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    
    self = [super initWithCoder:aDecoder];
    
    if (self) {
        self.imageLoader = [LSImageViewLoader loader];
    }
    return self;
}

- (void)updateHeadImageWith:(AudienModel *)audienModel radius:(int)radius {
    
    self.headImageView.layer.cornerRadius = radius * 0.5;
    self.headImageView.layer.masksToBounds = YES;
    
    [self.imageLoader stop];
    [self.imageLoader refreshCachedImage:self.headImageView options:SDWebImageRefreshCached imageUrl:audienModel.photoUrl
                        placeholderImage:audienModel.image];
    
    if (audienModel.isHasTicket) {
        self.showIcon.hidden = NO;
    }
    else
    {
        self.showIcon.hidden = YES;
    }
}

- (void)setCornerRadius:(CGFloat)radius{
    
    self.headImageView.layer.cornerRadius = radius;
}

- (void)awakeFromNib {
    [super awakeFromNib];
}

@end
