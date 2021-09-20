#include "slot_machine.h"

slot_machine::slot_machine(SDL_Renderer*& _renderer,
	float _fps,
	int _drum_count,
	const char* const* _paths,
	unsigned int _slot_count,
	int _x, int _y, int _w, int _h) noexcept
: drum_count(_drum_count), renderer(_renderer), fps(_fps)
{
	srand(time(0));

	viewport.x = _x;
	viewport.y = _y;
	viewport.w = _w;
	viewport.h = _h;

	drums = new drum * [_drum_count];
	for (int i = 0; i < drum_count; ++i)
	{
		drums[i] = new drum(_renderer, _paths, _slot_count,
			(_w / drum_count * i), 0, _w / drum_count, _h
		);
	}
}

slot_machine::~slot_machine() noexcept
{
	for (int i = 0; i < drum_count; ++i)
	{
		delete drums[i];
	}
	delete[] drums;
}



void slot_machine::slow_down_drums() noexcept
{
	for (int i = sdd_offset; i < drum_count; ++i)
	{
		if (drums[i - 1]->is_rotating() == false && drums[i]->is_rotating() == true)
		{
			drums[i]->set_rotation_params(drums[i]->get_rotation_speed(), drums[i]->get_rotation_speed() / 3.0f, fps);
			++sdd_offset;
			break;
		}
	}
}



void slot_machine::spin() noexcept
{
	sdd_offset = 1;

	for (int i = 0; i < drum_count; ++i)
		if (drums[i]->is_rotating() == true)
			return;

	unsigned int speed = 0;
	while (speed < 5)
		speed = rand() % 10;
	drums[0]->set_rotation_params((float)speed, (float)speed / 3.0f, fps);

	for (int i = 1; i < drum_count; ++i)
	{
		speed = 0;
		while(speed < 5)
			speed = rand() % 10;
		drums[i]->set_rotation_params((float)speed, 0.0f, fps);
	}
}


void slot_machine::draw() noexcept
{
	SDL_RenderSetViewport(renderer, &viewport);
	for (int i = 0; i < drum_count; ++i)
	{
		drums[i]->draw();
	}
	slow_down_drums();
}