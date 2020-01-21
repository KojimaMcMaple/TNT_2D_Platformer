#include "GameObject.h"

SDL_Rect* GameObject::GetSrcPosition() {
	return &src;
}
int GameObject::GetSrcPositionX() {
	return src.x;
}
int GameObject::GetSrcPositionY() {
	return src.y;
}
void GameObject::SetSrcPosition(int in_x, int in_y) {
	src.x = in_x;
	src.y = in_y;
}

// DST ACCESSOR MUTATOR
SDL_Rect* GameObject::GetDstPosition() {
	return &dst;
}
int GameObject::GetDstPositionX() {
	return dst.x;
}
int GameObject::GetDstPositionY() {
	return dst.y;
}
void GameObject::SetDstPosition(int in_x, int in_y) {
	dst.x = in_x;
	dst.y = in_y;
}

// TEXTURE ACCESSOR MUTATOR
SDL_Texture* GameObject::GetTexturePointer() {
	return texture;
}

int GameObject::GetSpeed() {
	return speed;
}
void GameObject::SetSpeed(int in_speed) {
	speed = in_speed;
}