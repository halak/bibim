#pragma once
#ifndef __BIBIM_AUDIO_BRIDGE_OBJECTIVEC_H__
#define __BIBIM_AUDIO_BRIDGE_OBJECTIVEC_H__

void BibimBGMPlay(void* proxy, const char* path);
void BibimBGMSetVolume(void* proxy, float volume);
void BibimSoundFXPlay(void* proxy, const char* path, int group);
void BibimSoundFXSetVolume(void* proxy, float volume);

#endif