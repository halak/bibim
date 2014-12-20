#import <Foundation/Foundation.h>
#import <AVFoundation/AVAudioPlayer.h>


@interface BGM : NSObject<AVAudioPlayerDelegate> {
    // NSMutableArray* voices;
}

- (id)init;
- (void)play:(NSString*)path;
- (void)setVolume:(NSNumber*)volume;

@end