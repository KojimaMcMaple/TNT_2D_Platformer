#pragma once

#include <string>

#include "GameObject.h"
#include "TextureManager.h"

class UI :public GameObject
{
public:
	UI(std::string texture_id, std::string texture_path, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h);
	~UI();

	void update() override;
	void draw() override;
	void clean() override;
};