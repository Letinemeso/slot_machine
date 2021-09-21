#include "slot_machine.h"

slot_machine::slot_machine(
	SDL_Renderer*& _renderer,
	SDL_Event& _event,
	float _fps,
	int _drum_count,
	const char* const* _paths,
	unsigned int _slot_count,
	const char* const* _button_paths,
	int _x, int _y, int _w, int _h) noexcept
: drum_count(_drum_count), renderer(_renderer), fps(_fps)
{
	srand(time(0));

	viewport.x = _x;
	viewport.y = _y;
	viewport.w = _w;
	viewport.h = _h / 8 * 6;

	button_viewport.x = 0;
	button_viewport.y = 0;
	button_viewport.w = _w + _x;
	button_viewport.h = _h + _y;

	drums = new drum * [_drum_count];
	for (int i = 0; i < drum_count; ++i)
	{
		drums[i] = new drum(_renderer, _paths, _slot_count,
			(_w / drum_count * i), 0, _w / drum_count, _h / 8 * 6
		);
	}

	btn = new button(renderer, _event, _button_paths, _w / 2 + _x, _h / 8 * 7 + _y, _h / 8 - _h / 16);
}

slot_machine::~slot_machine() noexcept
{
	for (int i = 0; i < drum_count; ++i)
	{
		delete drums[i];
	}
	delete[] drums;

	delete btn;
}



void slot_machine::slow_down_drums() noexcept
{
	for (int i = sdd_offset; i < drum_count; ++i)
	{
		if (drums[i - 1]->is_rotating() == false && drums[i]->is_rotating() == true)
		{
			drums[i]->set_rotation_params(drums[i]->get_rotation_speed(), drums[i]->get_rotation_speed() * 2.0f, fps);
			++sdd_offset;
			break;
		}
	}
}

void slot_machine::spin() noexcept
{
	for (int i = 0; i < drum_count; ++i)
		if (drums[i]->is_rotating() == true)
			return;

	sdd_offset = 1;

	unsigned int speed = 0;
	while (speed < 3)
		speed = rand() % 10;
	drums[0]->set_rotation_params((float)speed, (float)speed * 2.0f, fps);

	for (int i = 1; i < drum_count; ++i)
	{
		speed = 0;
		while(speed < 3)
			speed = rand() % 10;
		drums[i]->set_rotation_params((float)speed, 0.0f, fps);
	}
}



bool slot_machine::is_spinning() const noexcept
{
	for (int i = 0; i < drum_count; ++i)
		if (drums[i]->is_rotating() == true)
			return true;

	return false;
}

void slot_machine::draw() noexcept
{
	if (is_spinning() == true)
		btn->deactivate();
	else
		btn->activate();

	if (btn->is_pressed() == true) spin();		

	SDL_RenderSetViewport(renderer, &viewport);
	for (int i = 0; i < drum_count; ++i)
	{
		drums[i]->draw();
	}
	SDL_RenderSetViewport(renderer, &button_viewport);
	btn->draw();

	slow_down_drums();
}