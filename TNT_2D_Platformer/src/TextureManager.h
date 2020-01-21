#pragma once
#ifndef __TextureManager__
#define __TextureManager__

// Core Libraries
#include <iostream>
#include <string>
#include <map>

// SDL Libraries
#include<SDL.h>
#include<SDL_image.h>


class TextureManager {
public:
	static TextureManager* Instance()
	{
		if (sInstance == 0)
		{
			sInstance = new TextureManager();
			return sInstance;
		}

		return sInstance;
	}
	

	bool LoadTexture(std::string file_name, std::string id, SDL_Renderer* renderer_ptr);

	void Render(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer_ptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Render(std::string id, int x, int y, SDL_Renderer* renderer_ptr, bool is_centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void RenderFrame(std::string id, int x, int y, int width, int height, int current_row, int current_frame, SDL_Renderer* renderer_ptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void RenderFrame(std::string id, int x, int y, int current_row, int current_frame, SDL_Renderer* renderer_ptr, bool is_centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void SetAlpha(std::string id, Uint8 new_alpha);

private:

	TextureManager();
	~TextureManager();

	std::map<std::string, SDL_Texture*> texture_map;

	static TextureManager* sInstance;
};

typedef TextureManager TheTextureManager;

#endif /* defined(__TextureManager__) */