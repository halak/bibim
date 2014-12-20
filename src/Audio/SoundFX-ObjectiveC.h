#import <Foundation/Foundation.h>
#import <AVFoundation/AVAudioPlayer.h>


@interface SoundFX : NSObject<AVAudioPlayerDelegate> {
    // NSMutableArray* voices;
}

- (id)init;
- (void)play:(NSString*)path group:(NSNumber*)group;
- (void)setVolume:(NSNumber*)volume;

@end