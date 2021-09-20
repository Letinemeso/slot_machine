#ifndef __SLOT_MACHINE
#define __SLOT_MACHINE

#include "drum.h"
#include <ctime>

class slot_machine
{
private:
	const unsigned int drum_count;
	drum** drums;

	SDL_Renderer*& renderer;
	SDL_Rect viewport;

	float fps;

	unsigned int sdd_offset = 1;

private:
	void slow_down_drums() noexcept;

public:
	slot_machine(const slot_machine&) = delete;
	slot_machine(SDL_Renderer*& _renderer,
		float _fps,
		int _drum_count,
		const char* const* _paths,
		unsigned int _slot_count,
		int _x, int _y, int _w, int _h) noexcept;
	~slot_machine() noexcept;

	void spin() noexcept;

	void draw() noexcept;
};

#endif