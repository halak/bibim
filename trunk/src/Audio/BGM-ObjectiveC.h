#import <Foundation/Foundation.h>
#import <AVFoundation/AVAudioPlayer.h>


@interface BBBGM : NSObject<AVAudioPlayerDelegate> {
    // NSMutableArray* voices;
}

- (id)init;
- (void)play:(NSString*)path;
- (void)setVolume:(NSNumber*)volume;

@end