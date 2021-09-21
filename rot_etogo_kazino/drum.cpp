#include "drum.h"

drum::drum(SDL_Renderer*& _renderer,
	const char* const* const _paths,
	unsigned int _slot_count,
	int _x, int _y, int _w, int _h) noexcept
: slot_count(_slot_count), x(_x), y(_y), w(_w), h(_h), renderer(_renderer)
{
	max_shift = h / _slot_count;
	shift = (slot_count % 2 == 0 ? max_shift / 2 : 0);

	draw_order = new unsigned int[slot_count + 1];	//order in which objects will be drawn
	draw_order[0] = slot_count - 1;
	for (int i = 0; i < slot_count; ++i)
		draw_order[i + 1] = i;


	ys = new int[slot_count + 1];	//y positions for all objects, on which they will be drawn
	ys[0] = y - max_shift;
	for (int i = 1; i < slot_count + 1; ++i)
		ys[i] = y + (max_shift * (i - 1));


	slot = new screen_object * [slot_count];	//objects
	for (int i = 0; i < slot_count; ++i)	
	{
		slot[i] = new screen_object(_renderer);
		slot[i]->set_scale(w, h / slot_count);
		slot[i]->set_pos(x, y);
		slot[i]->set_texture(_paths[i]);
	}
}

drum::~drum() noexcept
{
	for (int i = 0; i < slot_count; ++i)
	{
		delete slot[i];
	}

	delete[] slot;

	delete[] draw_order;

	delete[] ys;
}



void drum::rotate_forward() noexcept
{
	unsigned int temp = draw_order[slot_count - 1];
	for (int i = slot_count; i > 0; --i)
	{
		draw_order[i] = draw_order[i - 1];
	}
	draw_order[0] = temp;

	shift -= max_shift;
}

void drum::rotate() noexcept
{
	if (rttn_spd > 0 && is_rotating_backward == false)
	{
		if (shift < max_shift)
		{
			shift += rttn_spd;

			if (ticks_until_dec == 0)
			{
				rttn_spd -= (dec_spd > rttn_spd ? rttn_spd : dec_spd);
				ticks_until_dec = orig_ticks_until_dec;
			}
			else
			{
				--ticks_until_dec;
			}
		}
		else
		{
			rotate_forward();
		}
	}
	else if (is_rotating_backward == true)
	{
		if (slot_count % 2 == 0)
		{
			if (abs((ys[slot_count / 2] + shift + (max_shift / 2)) - (h / 2)) > abs(rttn_spd))
			{
				shift -= rttn_spd;
			}
			else
			{
				shift = max_shift / 2;
				is_rotating_backward = false;
				rttn_spd = -1;
			}
		}
		else
		{
			int closest;

			if (ys[slot_count / 2 + 1] + shift < h / 2)
				closest = slot_count / 2 + 1;
			else
				closest = slot_count / 2;

			if (abs((ys[closest] + shift + (max_shift / 2)) - (h / 2)) > abs(rttn_spd))
			{
				shift -= rttn_spd;
			}
			else
			{
				if (closest == slot_count / 2)
					rotate_forward();
				shift = 0;
				is_rotating_backward = false;
				rttn_spd = -1;
			}
		}

	}
	else if (rttn_spd == 0 && is_rotating_backward == false)
	{
		if (slot_count % 2 == 0)
		{
			float move_by = -(float)((h / 2) - (ys[slot_count / 2] + shift + max_shift / 2)) / (float)max_shift;
			rttn_spd = (abs(h * move_by / fps) < 1 ? ((h * move_by / fps) < 0 ? -1 : 1) : h * move_by / fps);
		}
		else
		{
			int closest;
			if (ys[slot_count / 2 + 1] + shift < h / 2)
				closest = slot_count / 2 + 1;
			else
				closest = slot_count / 2;

			float move_by = -(float)((h / 2) - (ys[closest] + shift + max_shift / 2)) / (float)max_shift;
			rttn_spd = (abs(h * move_by / fps) < 1 ? ((h * move_by / fps) < 0 ? -1 : 1) : h * move_by / fps);
		}

		if (rttn_spd == 0)
			rttn_spd = -1;
		else
			is_rotating_backward = true;
	}
}



void drum::set_rotation_params(float _slots_per_second, float _deceleration_speed_in_sps, float _fps) noexcept
{
	fps = 1000.0f / _fps;

	rttn_spd = max_shift * _slots_per_second / fps;

	if (_deceleration_speed_in_sps < 0.0001f)
		dec_spd = 0;
	else if (max_shift * _deceleration_speed_in_sps / fps / 4 < 1.0f)
		dec_spd = 1;
	else
		dec_spd = max_shift * _deceleration_speed_in_sps / fps / 4;

	orig_ticks_until_dec = fps / 4;
	ticks_until_dec = fps / 4;
}



bool drum::is_rotating() const noexcept
{
	return (rttn_spd == -1 ? false : true);
}

float drum::get_rotation_speed() const noexcept
{
	if (is_rotating() == false) return 0;
		
	return rttn_spd * fps / max_shift;
}



void drum::draw() noexcept
{
	for (int i = 0; i < slot_count + 1; ++i)
	{
		slot[draw_order[i]]->set_pos(x, ys[i] + shift);

		slot[draw_order[i]]->draw();
	}

	rotate();
}