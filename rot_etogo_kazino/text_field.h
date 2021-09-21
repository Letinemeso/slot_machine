#ifndef __TEXT_FIELD
#define __TEXT_FIELD

#include "screen_object.h"
#include <string>

static bool initialized = false;

constexpr unsigned int sym_count = 36;
static std::string paths[sym_count];

class text_field
{
private:
	SDL_Renderer*& renderer;

	screen_object* background;
	screen_object* letter;
	SDL_Rect viewport;
	
	std::string text;

	int x, y, w, h;

private:
	unsigned int get_index(char _sym) const noexcept;

public:
	text_field(
		SDL_Renderer*& _renderer,
		const char* const _background_path,
		const char* const _letters_path,
		int _x, int _y, int _w, int _h) noexcept;
	~text_field() noexcept;

	void move_to(int _x, int _y) noexcept;
	void set_scale(int _w, int _h) noexcept;

	const std::string& get_text() const noexcept;
	void set_text(const char* const _text) noexcept;
	void add_sym(char _sym) noexcept;
	void add_num(int _num) noexcept;
	void add_num(float _num) noexcept;
	void clear_text() noexcept;

	void draw() noexcept;
};

#endif