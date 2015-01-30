#import "SoundFX-ObjectiveC.h"
#import "AudioBridge-ObjectiveC.h"

void BibimSoundFXPlay(void* proxy, const char* path, int group)
{
    NSString* stringPath = [NSString stringWithUTF8String: path];
    [(__bridge BBSoundFX*)proxy play:stringPath group:[NSNumber numberWithInt:group]];
}

void BibimSoundFXSetVolume(void* proxy, float volume)
{
    [(__bridge BBSoundFX*)proxy setVolume:[NSNumber numberWithFloat:volume]];
}

@implementation BBSoundFX

- (id)init
{
    self = [super init];

    if(self) 
    {
        sounds = [[NSMutableArray alloc] init];
        globalVolume = 1.0f;
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

- (void)play:(NSString*)path group:(NSNumber*)group
{
    NSURL* url = [NSURL fileURLWithPath : path];
    AVAudioPlayer *player = [[AVAudioPlayer alloc] initWithContentsOfURL:url error: NULL];
    if (player) {
        [player prepareToPlay];
        [player setVolume:globalVolume];
        [player setDelegate:self];
        [player play];
        [sounds addObject:player];
    }
    

    // AVAudioPlayer * player = [voices objectAtIndex:playIndex];
    // [player setCurrentTime:0.0];
    // player.numberOfLoops = 0;
    // [player play];
    // playIndex += 1;
    // playIndex = playIndex % [voices count];
}

- (void)setVolume:(NSNumber *)volume
{
    globalVolume = [volume floatValue];
    for (AVAudioPlayer* sound in sounds) {
        [sound setVolume:globalVolume];
    }
}

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player
                       successfully:(BOOL)flag
{
    [sounds removeObject:player];
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