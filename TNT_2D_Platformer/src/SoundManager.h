#pragma once
#ifndef __SoundManager__
#define __SoundManager__

// Core Libraries
#include <iostream>
#include <string>
#include <map> 

#include <SDL_mixer.h>
#include "SoundId.h"

class SoundManager {
public:
	static SoundManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new SoundManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(std::string fileName, SoundId id, SoundType type);
	void freeAllSounds();

	void playSound(SoundId id, int loop);
	void playMusic(SoundId id, int loop);
private:
	SoundManager();
	~SoundManager();
	SoundManager(const SoundManager&);

	static SoundManager* s_pInstance;

	std::map<SoundId, Mix_Chunk*> m_sfxs;
	std::map<SoundId, Mix_Music*> m_music;
};

typedef SoundManager TheSoundManager;

#endif /* defined (__SoundManager__) */