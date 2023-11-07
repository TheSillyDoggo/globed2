#pragma once
#include <defs.hpp>

#if GLOBED_VOICE_SUPPORT

#include "audio_frame.hpp"
#include "audio_stream.hpp"
#include <chrono>

/*
* VoicePlaybackManager is responsible for playing voices of multiple people
* at the same time efficiently and without memory leaks.
*/
class VoicePlaybackManager {
public:
    GLOBED_SINGLETON(VoicePlaybackManager);
    VoicePlaybackManager();
    ~VoicePlaybackManager();

    void playFrameStreamed(int playerId, const EncodedAudioFrame& frame);

    void releaseStaleSounds();

private:
    std::vector<std::pair<std::chrono::milliseconds, FMOD::Sound*>> activeSounds;

    std::unordered_map<int, std::unique_ptr<AudioStream>> streams;
};

#endif // GLOBED_VOICE_SUPPORT