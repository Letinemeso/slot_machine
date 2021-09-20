#ifndef __DRUM
#define __DRUM

#include "log_macro.h"
#include "screen_object.h"

class drum
{
private:
	const unsigned int slot_count;
	screen_object** slot;

	SDL_Renderer*& renderer;
	int* ys;

	unsigned int* draw_order;

	int x, y, w, h;

	float fps = -1.0f;
	bool is_rotating_backward = false;

	int rttn_spd = -1, dec_spd = 0, ticks_until_dec = 0, orig_ticks_until_dec = 0;
	int shift, max_shift;

private:
	void rotate_forward() noexcept;
	void rotate() noexcept;

public:
	drum(const drum&) = delete;
	drum(SDL_Renderer*& _renderer,
		const char* const *_paths,
		unsigned int _slot_count,
		int _x, int _y, int _w, int _h) noexcept;
	~drum() noexcept;

	void set_rotation_params(float _slots_per_second, float _deceleration_speed_in_sps, float _fps) noexcept;

	bool is_rotating() const noexcept;
	float get_rotation_speed() const noexcept;

	void draw() noexcept;

};

#endif