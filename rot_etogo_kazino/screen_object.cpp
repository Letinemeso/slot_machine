#include "screen_object.h"

screen_object::screen_object(SDL_Renderer*& _renderer) noexcept
	:renderer(_renderer)
{ }

screen_object::screen_object(SDL_Renderer*& _renderer, const char* const _path, int _x, int _y, int _w, int _h) noexcept
	:renderer(_renderer)
{
	SDL_Surface* temp = IMG_Load(_path);

	if (temp == nullptr)
	{
		LOG("error: ", SDL_GetError(), "\n\n");
		return;
	}

	texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	if (texture == nullptr)
	{
		LOG("error: ", SDL_GetError(), "\n\n");
		return;
	}

	transform.x = _x;
	transform.y = _y;
	transform.w = _w;
	transform.h = _h;
}

screen_object::~screen_object() noexcept
{
	if (texture == nullptr)
	{
		SDL_DestroyTexture(texture);
	}
}



void screen_object::set_texture(const char* const _path) noexcept
{
	SDL_Surface* temp = IMG_Load(_path);

	if (temp == nullptr)
	{
		LOG("error: ", SDL_GetError(), "\n\n");
		return;
	}

	if (texture != nullptr) SDL_DestroyTexture(texture);

	texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	if (texture == nullptr)
	{
		LOG("error: ", SDL_GetError(), "\n\n");
		return;
	}
}

void screen_object::set_scale(int _w, int _h) noexcept
{
	transform.w = _w;
	transform.h = _h;
}

void screen_object::set_pos(int _x, int _y) noexcept
{
	transform.x = _x;
	transform.y = _y;
}

void screen_object::move(int _x, int _y) noexcept
{
	transform.x += _x;
	transform.y += _y;
}



int screen_object::x() const noexcept
{
	return transform.x;
}

int screen_object::y() const noexcept
{
	return transform.y;
}



void screen_object::draw() noexcept
{
	if (texture != nullptr)
		SDL_RenderCopy(renderer, texture, nullptr, &transform);
	else
		LOG("error: unable to draw\n\n", "", "");
}