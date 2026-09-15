#include "AudioManager.h"
#include "Logger.h"

AudioManager::AudioManager()
{
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO))
    {
        Logger::Err(std::string("Audio init failed: ") + SDL_GetError());
        return;
    }

    m_deviceId = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (m_deviceId == 0)
    {
        Logger::Err(std::string("Could not open default audio playback device: ") + SDL_GetError());
        return;
    }

    m_initialized = true;
    Logger::Log("AudioManager initialized");
}

AudioManager::~AudioManager()
{
    StopMusic();

    for (auto& [name, clip] : m_sounds) FreeClipData(clip);
    m_sounds.clear();

    FreeClipData(m_music);

    if (m_deviceId != 0) SDL_CloseAudioDevice(m_deviceId);

    Logger::Log("AudioManager destroyed");
}

void AudioManager::FreeClipData(AudioClip& clip)
{
    if (clip.stream) { SDL_DestroyAudioStream(clip.stream); clip.stream = nullptr; }
    if (clip.buffer) { SDL_free(clip.buffer);               clip.buffer = nullptr; }
    clip.length = 0;
}

bool AudioManager::LoadWavInto(AudioClip& clip, std::string_view filename)
{
    return SDL_LoadWAV(std::string(filename).c_str(), &clip.spec, &clip.buffer, &clip.length);
}

bool AudioManager::BindClip(AudioClip& clip, float gain)
{
    clip.stream = SDL_CreateAudioStream(&clip.spec, nullptr);
    if (!clip.stream)
    {
        Logger::Err(std::string("CreateAudioStream failed: ") + SDL_GetError());
        return false;
    }

    if (!SDL_BindAudioStream(m_deviceId, clip.stream))
    {
        Logger::Err(std::string("BindAudioStream failed: ") + SDL_GetError());
        SDL_DestroyAudioStream(clip.stream);
        clip.stream = nullptr;
        return false;
    }

    SDL_SetAudioStreamGain(clip.stream, gain);
    return true;
}

bool AudioManager::LoadSound(std::string_view name, std::string_view filename)
{
    if (!m_initialized) return false;

    AudioClip clip;
    if (!LoadWavInto(clip, filename))
    {
        Logger::Err(std::string("Failed to load sound '") + std::string(name)
                    + "' from " + std::string(filename) + ": " + SDL_GetError());
        return false;
    }

    if (!BindClip(clip, m_soundVolume))
    {
        FreeClipData(clip);
        return false;
    }

    Logger::Log(std::string("Sound loaded: ") + std::string(name) + " <- " + std::string(filename));
    m_sounds.emplace(std::string(name), clip);
    return true;
}

bool AudioManager::LoadMusic(std::string_view filename)
{
    if (!m_initialized) return false;

    FreeClipData(m_music);

    if (!LoadWavInto(m_music, filename))
    {
        Logger::Err(std::string("Failed to load music from ") + std::string(filename)
                    + ": " + SDL_GetError());
        return false;
    }

    if (!BindClip(m_music, m_musicVolume))
    {
        FreeClipData(m_music);
        return false;
    }

    Logger::Log(std::string("Music loaded: ") + std::string(filename));
    return true;
}

void AudioManager::PlaySfx(std::string_view name)
{
    if (!m_initialized) return;

    auto it = m_sounds.find(std::string(name));
    if (it == m_sounds.end()) 
        return;

    AudioClip& clip = it->second;
    if (!clip.stream || !clip.buffer) return;

    
    SDL_ClearAudioStream(clip.stream);
    SDL_PutAudioStreamData(clip.stream, clip.buffer, clip.length);
}

void AudioManager::StartMusic()
{
    if (!m_initialized || !m_music.stream || !m_music.buffer) 
        return;
    
    
    SDL_ClearAudioStream(m_music.stream);
    SDL_PutAudioStreamData(m_music.stream, m_music.buffer, m_music.length);
    m_isMusicPlaying = true;
    
}

void AudioManager::StopMusic()
{
    if (!m_music.stream) return;
    SDL_ClearAudioStream(m_music.stream);
    m_isMusicPlaying = false;
}

void AudioManager::Update()
{
    if (!m_initialized || !m_isMusicPlaying || !m_music.stream || !m_music.buffer) return;

    
    const int queued = SDL_GetAudioStreamQueued(m_music.stream);
    
    
    if (queued < static_cast<int>(m_music.length / 4))
        SDL_PutAudioStreamData(m_music.stream, m_music.buffer, m_music.length);
    
}

void AudioManager::SetSoundVolume(float v)
{
    m_soundVolume = v;
    for (auto& [name, clip] : m_sounds)
        if (clip.stream) SDL_SetAudioStreamGain(clip.stream, m_soundVolume);
}

void AudioManager::SetMusicVolume(float v)
{
    m_musicVolume = v;
    if (m_music.stream) SDL_SetAudioStreamGain(m_music.stream, m_musicVolume);
}