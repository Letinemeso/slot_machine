#ifndef __BUTTON
#define __BUTTON

#include "screen_object.h"

class button
{
private:
	screen_object* bright;
	screen_object* dim;

	SDL_Event& event;

	int center_x, center_y, radius;

	bool pressed = false;

public:
	button(
		SDL_Renderer*& _renderer, 
		SDL_Event& _event,
		const char* const* _paths,
		int _center_x, int _center_y, int _radius
	) noexcept;
	~button() noexcept;

	bool is_pressed(int _x, int _y) noexcept;

};

#endif