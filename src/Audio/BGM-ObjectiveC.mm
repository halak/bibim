#import "BGM-ObjectiveC.h"
#import "AudioBridge-ObjectiveC.h"

void BibimBGMPlay(void* proxy, const char* path)
{
    NSString* stringPath = [NSString stringWithUTF8String: path];
    [(__bridge BBBGM*)proxy play:stringPath];
}

void BibimBGMSetVolume(void* proxy, float volume)
{
    [(__bridge BBBGM*)proxy setVolume:[NSNumber numberWithFloat:volume]];
}

@implementation BBBGM

- (id)init
{
    self = [super init];

    if(self) 
    {
        // voices = [[NSMutableArray alloc] init];
        // NSURL *pathURL = [NSURL fileURLWithPath : path];
        
        // for (int x = 0; x < [numVoices intValue]; x++) 
        // {
        //     AVAudioPlayer *player;
        //     player = [[AVAudioPlayer alloc] initWithContentsOfURL:pathURL error: NULL];
        //     [player prepareToPlay];
        //     [voices addObject:player];
        // }
        
        // playIndex = 0;
    }

    return(self);
}

- (void)play:(NSString*)path
{
    NSURL* url = [NSURL fileURLWithPath : path];
    AVAudioPlayer *player = [[AVAudioPlayer alloc] initWithContentsOfURL:url error: NULL];
    [player prepareToPlay];
    [player play];
    // AVAudioPlayer * player = [voices objectAtIndex:playIndex];
    // [player setCurrentTime:0.0];
    // player.numberOfLoops = 0;
    // [player play];
    // playIndex += 1;
    // playIndex = playIndex % [voices count];
}

- (void)setVolume:(NSNumber*)volume
{
}

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player
                       successfully:(BOOL)flag
{
}

- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player
                                 error:(NSError *)error
{
}

// - (void) stop
// {
//     for (int x = 0; x < [voices count]; x++) 
//     {
//         AVAudioPlayer * player = [voices objectAtIndex:x];
//         [player stop];
//     }
// }

// - (void) loop
// {
//     [self stop];
//     AVAudioPlayer * player = [voices objectAtIndex:playIndex];
//     [player setCurrentTime:0.0];
//     player.numberOfLoops = -1;
//     [player play];
//     playIndex += 1;
//     playIndex = playIndex % [voices count];
// }

// - (void) unload 
// {
//     [self stop];
// }

@end