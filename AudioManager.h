#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <string_view>
#include <unordered_map>

struct AudioClip
{
    SDL_AudioSpec    spec   = {};
    Uint8*           buffer = nullptr;
    Uint32           length = 0;
    SDL_AudioStream* stream = nullptr;
    
    
};

namespace AudioAssets
{
    namespace Sfx
    {
        inline constexpr std::string_view SHOOT = "shoot";
        inline constexpr std::string_view HIT = "hit";
        inline constexpr std::string_view PICKUP_SPREAD = "pickup_spread";
        inline constexpr std::string_view PICKUP_HEAL="pickup_heal";
    }
    
    
    inline const std::string BASE_PATH = "./Assets/Sounds/";
    
    
    namespace SfxPath
    {
        inline constexpr std::string_view HIT="hit.wav";
        inline constexpr std::string_view PICKUP_SPREAD="pickup_spread.wav";
        inline constexpr std::string_view PICKUP_HEAL="pickup_heal.wav";
        inline constexpr std::string_view MUSIC="music.wav";
        inline constexpr std::string_view SHOOT="shoot.wav";
    }
}

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    AudioManager(const AudioManager&)            = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    bool LoadSound(std::string_view name, std::string_view filename);
    
    bool LoadMusic(std::string_view filename);

    void PlaySfx(std::string_view name);

    
    void StartMusic();
    void StopMusic();
    void Update();

    
    void SetSoundVolume(float v);
    void SetMusicVolume(float v);

private:
    bool LoadWavInto(AudioClip& clip, std::string_view filename);
    bool BindClip(AudioClip& clip, float gain);
    void FreeClipData(AudioClip& clip);

    SDL_AudioDeviceID m_deviceId      = 0;
    bool              m_initialized = false;

    std::unordered_map<std::string, AudioClip> m_sounds;
    AudioClip m_music;
    bool      m_isMusicPlaying = false;

    float m_soundVolume = 1.0f;
    float m_musicVolume = 1.0f;
};