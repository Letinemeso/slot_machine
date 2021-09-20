#ifndef __SCREEN_OBJECT
#define __SCREEN_OBJECT

#include <SDL.h>
#include <SDL_image.h>

#include "log_macro.h"

class screen_object
{
private:
	SDL_Texture* texture = nullptr;
	SDL_Rect transform = { 0, 0, 0, 0 };
	SDL_Renderer*& renderer;

public:
	screen_object(const screen_object&) = delete;
	screen_object(SDL_Renderer*& _renderer) noexcept;
	screen_object(SDL_Renderer*& _renderer, 
		const char* const _path, 
		int _x, int _y, int _w, int _h) noexcept;
	~screen_object() noexcept;

	void set_texture(const char* const _path) noexcept;
	void set_scale(int _w, int _h) noexcept;
	void set_pos(int _x, int _y) noexcept;
	void move(int _x, int _y) noexcept;

	int x() const noexcept;
	int y() const noexcept;

	void draw() noexcept;
};

#endif