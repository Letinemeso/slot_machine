#ifndef __SLOT_MACHINE
#define __SLOT_MACHINE

#include "drum.h"
#include "button.h"

#include <ctime>

class slot_machine
{
private:
	const unsigned int drum_count;
	drum** drums;
	button* btn;

	SDL_Renderer*& renderer;
	SDL_Rect viewport;
	SDL_Rect button_viewport;

	float fps;

	unsigned int sdd_offset = 1;

private:
	void slow_down_drums() noexcept;
	void spin() noexcept;

public:
	slot_machine(const slot_machine&) = delete;
	slot_machine(
		SDL_Renderer*& _renderer,
		SDL_Event& _event,
		float _fps,
		int _drum_count,
		const char* const* _paths,
		unsigned int _slot_count,
		const char* const* _button_paths,
		int _x, int _y, int _w, int _h) noexcept;
	~slot_machine() noexcept;

	bool is_spinning() const noexcept;

	void draw() noexcept;
};

#endif