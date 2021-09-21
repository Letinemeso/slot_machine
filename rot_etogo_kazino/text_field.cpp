#include "text_field.h"

text_field::text_field(
	SDL_Renderer*& _renderer,
	const char* const _background_path,
	const char* const _letters_path,
	int _x, int _y, int _w, int _h) noexcept
: renderer(_renderer), x(_x), y(_y), w(_w), h(_h)
{
	if (initialized == false)
	{
		for (int i = 0; i < 10; ++i)
		{
			paths[i] += _letters_path;
			paths[i] += char('0' + i);
			paths[i] += ".png";
		}
		for (int i = 10; i < sym_count; ++i)
		{
			paths[i] += _letters_path;
			paths[i] += char('a' + i - 10);
			paths[i] += ".png";
		}
		initialized = true;
	}

	letter = new screen_object(_renderer);
	background = new screen_object(_renderer, _background_path, _x, _y, _w, _h);

	viewport.x = 0;
	viewport.y = 0;
	viewport.w = w + x;
	viewport.h = h + y;
}

text_field::~text_field() noexcept
{
	delete background;
	delete letter;
}



unsigned int text_field::get_index(char _sym) const noexcept
{
	if (_sym <= '9' && _sym >= '0')
		return _sym - '0';
	else if (_sym <= 'z' && _sym >= 'a')
		return _sym - 'a' + 10;
	else if (_sym <= 'Z' && _sym >= 'A')
		return _sym - 'A' + 10;
	else
		return 0;
}



void text_field::move_to(int _x, int _y) noexcept
{
	x = _x;
	y = _y;

	viewport.w = w + x;
	viewport.h = h + y;
}

void text_field::set_scale(int _w, int _h) noexcept
{
	w = _w;
	h = _h;

	viewport.w = w + x;
	viewport.h = h + y;
}



const std::string& text_field::get_text() const noexcept
{
	return text;
}

void text_field::set_text(const char* const _text) noexcept
{
	text = _text;
}

void text_field::add_sym(char _sym) noexcept
{
	text += _sym;
}

void text_field::add_num(int _num) noexcept
{
	text += std::to_string(_num);
}

void text_field::add_num(float _num) noexcept
{
	text += std::to_string(_num);
}

void text_field::clear_text() noexcept
{
	text.clear();
}



void text_field::draw() noexcept
{
	SDL_RenderSetViewport(renderer, &viewport);
	background->draw();

	if (text.size() > 0)
	{
		int letter_width = (w / text.size() > 1 ? w / text.size() : 1);
		letter->set_scale(letter_width, h);

		for (int i = 0; i < text.size(); ++i)
		{
			if (text[i] == ' ') continue;

			letter->set_texture(paths[get_index(text[i])].c_str());
			letter->set_pos(x + letter_width * i, y);

			letter->draw();
		}
	}
}