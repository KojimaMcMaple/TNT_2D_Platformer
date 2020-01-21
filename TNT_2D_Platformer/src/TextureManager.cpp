#include "TextureManager.h"

TextureManager* TextureManager::sInstance = 0;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

bool TextureManager::LoadTexture(std::string file_name, std::string id, SDL_Renderer* renderer_ptr)
{
	SDL_Surface* temp_surface_ptr = IMG_Load(file_name.c_str());

	if (temp_surface_ptr == 0)
	{
		return false;
	}
	SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, temp_surface_ptr);

	SDL_FreeSurface(temp_surface_ptr);

	// everything went ok, add the texture to our list
	if (texture_ptr != 0)
	{
		texture_map[id] = texture_ptr;
		return true;
	}
	// reaching here means something went wrong
	return false;
}

void TextureManager::Render(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer_ptr, SDL_RendererFlip flip)
{
	SDL_Rect src_rect;
	SDL_Rect dest_rect;
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = dest_rect.w = width;
	src_rect.h = dest_rect.h = height;
	dest_rect.x = x;
	dest_rect.y = y;
	SDL_RenderCopyEx(renderer_ptr, texture_map[id], &src_rect, &dest_rect, 0, 0, flip);
}

void TextureManager::Render(std::string id, int x, int y, SDL_Renderer* renderer_ptr, bool is_centered, SDL_RendererFlip flip)
{
	SDL_Rect src_rect;
	SDL_Rect dest_rect;

	src_rect.x = 0;
	src_rect.y = 0;

	int texture_width, texture_height;

	SDL_QueryTexture(texture_map[id], NULL, NULL, &texture_width, &texture_height);

	src_rect.w = dest_rect.w = texture_width;
	src_rect.h = dest_rect.h = texture_height;

	if (is_centered) {
		int x_offset = texture_width * 0.5;
		int y_offset = texture_height * 0.5;
		dest_rect.x = x - x_offset;
		dest_rect.y = y - y_offset;
	}
	else {
		dest_rect.x = x;
		dest_rect.y = y;
	}

	SDL_RenderCopyEx(renderer_ptr, texture_map[id], &src_rect, &dest_rect, 0, 0, flip);
}

void TextureManager::RenderFrame(std::string id, int x, int y, int width, int height, int current_row, int current_frame, SDL_Renderer* renderer_ptr, SDL_RendererFlip flip)
{
	SDL_Rect src_rect;
	SDL_Rect dest_rect;

	src_rect.x = width * current_frame;
	src_rect.y = height * (current_row - 1);
	src_rect.w = dest_rect.w = width;
	src_rect.h = dest_rect.h = height;
	dest_rect.x = x;
	dest_rect.y = y;
	SDL_RenderCopyEx(renderer_ptr, texture_map[id], &src_rect, &dest_rect, 0, 0, flip);
}

void TextureManager::RenderFrame(std::string id, int x, int y, int current_row, int current_frame, SDL_Renderer* renderer_ptr, bool is_centered, SDL_RendererFlip flip)
{
	SDL_Rect src_rect;
	SDL_Rect dest_rect;

	int texture_width, texture_height;

	SDL_QueryTexture(texture_map[id], NULL, NULL, &texture_width, &texture_height);

	src_rect.x = texture_width * current_frame;
	src_rect.y = texture_height * (current_row - 1);
	src_rect.w = dest_rect.w = texture_width;
	src_rect.h = dest_rect.h = texture_height;

	if (is_centered) {
		int x_offset = texture_width * 0.5;
		int y_offset = texture_height * 0.5;
		dest_rect.x = x - x_offset;
		dest_rect.y = y - y_offset;
	}
	else {
		dest_rect.x = x;
		dest_rect.y = y;
	}

	SDL_RenderCopyEx(renderer_ptr, texture_map[id], &src_rect, &dest_rect, 0, 0, flip);
}

void TextureManager::SetAlpha(std::string id, Uint8 new_alpha)
{
	SDL_Texture* texture_ptr = texture_map[id];
	SDL_SetTextureAlphaMod(texture_ptr, new_alpha);
}
