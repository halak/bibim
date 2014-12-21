#import <Foundation/Foundation.h>
#import <AVFoundation/AVAudioPlayer.h>


@interface BBSoundFX : NSObject<AVAudioPlayerDelegate> {
    float globalVolume;
    NSMutableArray* sounds;
}

- (id)init;
- (void)play:(NSString*)path group:(NSNumber*)group;
- (void)setVolume:(NSNumber*)volume;

@end