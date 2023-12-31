#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
    m_AudioEngine = irrklang::createIrrKlangDevice();
    // specify the audio fall-off factor as Lucid isn't based on real-world parameters
    m_AudioEngine->setDefault3DSoundMinDistance(15.0f);
    m_AudioEngine->setRolloffFactor(0.1f);
}

AudioEngine::~AudioEngine()
{
	delete m_AudioEngine;
}

void AudioEngine::PlaySound(std::string name, bool loop, float volume, bool startRandom)
{
    // IDEA(Joey): create ring buffer of audio play requests that are only played during 
    // engine's update call; at the end of each frame. This allows us to only query
    // the driver at one point of time and allows us to dismiss/combine overlapping
    // audio requests...
    if (loop && m_AudioEngine->isCurrentlyPlaying(m_AudioEngine->getSoundSource(name.c_str())))
        return;
    irrklang::ISound *sound = m_AudioEngine->play2D(name.c_str(), loop, true);
    if (sound)
    {
        if (startRandom) // if start random, start audio at random buffer offset
           sound->setPlayPosition(rand() % (sound->getPlayLength() - 1));
        sound->setVolume(volume);
        sound->setIsPaused(false);
    }
}

void AudioEngine::PlaySoundLocation(std::string name, glm::vec2 location, bool loop, float volume, bool startRandom)
{
    irrklang::ISound *sound = m_AudioEngine->play3D(name.c_str(), irrklang::vec3df(location.x, location.y, 0.0), loop, true);
    if (sound)
    {
        if (startRandom) // if start random, start audio at random buffer offset
            sound->setPlayPosition(rand() % (sound->getPlayLength() - 1));
        sound->setVolume(volume);
        sound->setIsPaused(false);
    }
}

void AudioEngine::StopSound(std::string name)
{
    m_AudioEngine->removeSoundSource(name.c_str());
}
void AudioEngine::StopAll()
{
    m_AudioEngine->stopAllSounds();
}

void AudioEngine::SetPlayerPosition(glm::vec2 position)
{
    m_AudioEngine->setListenerPosition(irrklang::vec3df(position.x, position.y, 0.0f), irrklang::vec3df(0.0f, 0.0f, 0.0f)); 
}

void AudioEngine::PreLoad()
{
    m_AudioEngine->addSoundSourceFromFile("audio/menu.mp3",         irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
    m_AudioEngine->addSoundSourceFromFile("audio/ambient1.mp3",     irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
    m_AudioEngine->addSoundSourceFromFile("audio/ambient2.mp3",     irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
    m_AudioEngine->addSoundSourceFromFile("audio/ambient3.mp3",     irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
    m_AudioEngine->addSoundSourceFromFile("audio/scene_intro.mp3",  irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
    m_AudioEngine->addSoundSourceFromFile("audio/death.mp3",        irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
    m_AudioEngine->addSoundSourceFromFile("audio/fire.mp3",         irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
    m_AudioEngine->addSoundSourceFromFile("audio/jump.mp3",         irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
    m_AudioEngine->addSoundSourceFromFile("audio/light_switch.mp3", irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
    //m_AudioEngine->addSoundSourceFromFile("audio/enemy1.mp3",       irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
    //m_AudioEngine->addSoundSourceFromFile("audio/enemy2.mp3",       irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
}