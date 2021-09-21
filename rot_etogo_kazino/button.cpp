#include "button.h"

button::button(
	SDL_Renderer*& _renderer, 
	SDL_Event& _event,
	const char* const* _paths,
	int _center_x, int _center_y, int _radius) noexcept 
: event(_event), center_x(_center_x), center_y(_center_y), radius(_radius)
{

	bright = new screen_object(_renderer, _paths[0], center_x - radius, center_y - radius, radius * 2, radius * 2);
	dim = new screen_object(_renderer, _paths[1], center_x - radius, center_y - radius, radius * 2, radius * 2);
}

button::~button() noexcept
{
	delete bright;
	delete dim;
}



bool button::is_pressed() noexcept
{
	if (active == false) return false;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			int distance = pow(((event.button.x - center_x) * (event.button.x - center_x)) + ((event.button.y - center_y) * (event.button.y - center_y)), 0.5f);

			if (distance <= radius)
			{
				return true;
			}
		}
	}
	return false;
}



void button::activate() noexcept
{
	active = true;
}

void button::deactivate() noexcept
{
	active = false;
}



void button::draw() noexcept
{
	if (active == true)
		if (is_pressed() == false)
			bright->draw();
		else
			dim->draw();
	else
		dim->draw();
}