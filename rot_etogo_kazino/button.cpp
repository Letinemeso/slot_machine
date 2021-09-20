#include "button.h"

button::button(
	SDL_Renderer*& _renderer, 
	SDL_Event& _event,
	const char* const* _paths,
	int _center_x, int _center_y, int _radius
) noexcept : event(_event), center_x(_center_x), center_y(_center_y), radius(_radius)
{

	bright = new screen_object(_renderer, _paths[0], center_x - radius, center_y - radius, radius * 2, radius * 2);
	dim = new screen_object(_renderer, _paths[1], center_x - radius, center_y - radius, radius * 2, radius * 2);
}

bool button::is_pressed(int _x, int _y) noexcept
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			int distance = pow(((event.button.x - center_x) * (event.button.x - center_x)) + ((event.button.y - center_y) * (event.button.y - center_y)), 0.5f);

			if (distance <= radius)
			{
				pressed = true;
				return true;
			}
		}
	}

	pressed = false;
	return false;
}
