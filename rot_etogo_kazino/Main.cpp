#include "log_macro.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "screen_object.h"
#include "drum.h"
#include "slot_machine.h"
#include "button.h"
#include "text_field.h"

constexpr int scr_width	 = 1360;
constexpr int scr_height = 780;

constexpr int xx = 20;
constexpr int yy = 20;
constexpr int ww = 800 - 50 - xx;
constexpr int hh = 600 - 20 - yy;

int main()
{
	SDL_Window* window = nullptr;
	//SDL_Surface* surface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("Initialization error: ", SDL_GetError(), "\n\n");
		return -1;
	}
	else
	{
		window = SDL_CreateWindow("airstream", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scr_width, scr_height, SDL_WINDOW_SHOWN);

		if (window == nullptr)
		{
			LOG("window creation error: ", SDL_GetError(), "\n\n");
			return -1;
		}
	}
	//surface = SDL_GetWindowSurface(window);

	//initing sdl_img
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		LOG("error initializing png: ", IMG_GetError(), "\n\n");
		return -1;
	}


	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr)
	{
		LOG("renderer: ", SDL_GetError(), "\n\n");
		return -1;
	}

	screen_object background(renderer, "background.bmp", 0, 0, scr_width, scr_height);
	screen_object line(renderer, "line.png", 0, 0, scr_width, scr_height);
	
	text_field tf(renderer, "textures/background.png", "textures/letters/", scr_width / 6 * 5, scr_height / 20 * 19, scr_width / 6, scr_height / 20);

	const char* const paths[3] = {
		"textures/drum_symbols/drum_symbol_cherry.png",
		"textures/drum_symbols/drum_symbol_icecream.png",
		"textures/drum_symbols/drum_symbol_clover.png"
	};
	const char* const button_paths[2] = {
		"textures/button/active.png",
		"textures/button/inactive.png"
	};

	SDL_Event event;

	slot_machine machine(
		renderer, 
		event, 
		1000.0f / 60.0f, 
		5, 
		paths, 
		3, 
		button_paths,
		scr_width / 10, scr_height / 10, scr_width / 10 * 8, scr_height / 10 * 9
	);

	SDL_Rect viewport = { 0, 0, scr_width, scr_height };

	bool need_to_quit = false;

	std::chrono::time_point<std::chrono::high_resolution_clock> begin;
	std::chrono::time_point<std::chrono::high_resolution_clock> end;

	float time = 0.0f;
	int frames = 0;
	while (need_to_quit == false)
	{
		begin = std::chrono::high_resolution_clock::now();

		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) { need_to_quit = true; }

		SDL_RenderClear(renderer);
		
		if (time > 1.0f)
		{
			tf.clear_text();
			tf.set_text("fps ");
			tf.add_num(frames);

			frames = 0;
			time = 0.0f;
		}
		
		tf.draw();
		machine.draw();

		SDL_RenderSetViewport(renderer, &viewport);

		SDL_RenderPresent(renderer);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
		
		end = std::chrono::high_resolution_clock::now();
		time += std::chrono::duration_cast<std::chrono::duration<float>>(end - begin).count();
		++frames;
	}

	IMG_Quit();
	SDL_Quit();

	return 0;
}