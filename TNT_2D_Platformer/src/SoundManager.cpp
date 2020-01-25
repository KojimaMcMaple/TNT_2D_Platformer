#include "SoundManager.h"

SoundManager* SoundManager::s_pInstance;

SoundManager::SoundManager()
{
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048);
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
		if (pMusic == 0)
		{
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}

		m_music[id] = pMusic;
		return true;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
		if (pChunk == 0)
		{
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}

		m_sfxs[id] = pChunk;
		return true;
	}
	return false;
}

void SoundManager::freeAllSounds()
{
	std::map<std::string, Mix_Chunk*>::iterator it_sfx = s_pInstance->m_sfxs.begin();
	for (std::pair<std::string, Mix_Chunk*> elem_sfx : s_pInstance->m_sfxs)
	{
		Mix_FreeChunk(elem_sfx.second);
	}

	std::map<std::string, Mix_Music*>::iterator it_music = s_pInstance->m_music.begin();
	for (std::pair<std::string, Mix_Music*> elem_music : s_pInstance->m_music)
	{
		Mix_FreeMusic(elem_music.second);
	}
}

void SoundManager::playMusic(std::string id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(std::string id, int loop)
{
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}
