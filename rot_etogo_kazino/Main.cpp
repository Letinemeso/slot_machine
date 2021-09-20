#include "log_macro.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "screen_object.h"
#include "drum.h"
#include "slot_machine.h"

constexpr int scr_width	 = 800;
constexpr int scr_height = 600;

constexpr int xx = 20;
constexpr int yy = 20;
constexpr int ww = 800 - 50 - xx;
constexpr int hh = 600 - 20 - yy;

int main()
{
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;

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
	surface = SDL_GetWindowSurface(window);

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
	

	const char* const paths[4] = {
		"textures/drum_symbol_cherry.png",
		"textures/drum_symbol_icecream.png",
		"textures/drum_symbol_clover.png",
		"textures/drum_symbol_bass.png"
	};

	slot_machine machine(renderer, 1000.0f / 60.0f, 5, paths, 3,
		100, 50, scr_width - 200, scr_height - 200
	);

	//drum d(renderer, paths, 3, 0, 0, 200, 600);

	bool need_to_quit = false;

	SDL_Event event;

	while (need_to_quit == false)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) { need_to_quit = true; }

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				/*if (d.is_rotating() == false)
				{
					d.set_rotation_params(2.0f, 1.0f, 1000.0f / 60.0f);
				}*/
				machine.spin();
			}
		}

		SDL_RenderClear(renderer);
		
		//LOG("rttnspd: ", d.is_rotating(), "\n\n");
		//d.draw();

		machine.draw();

		//line.draw();

		SDL_RenderPresent(renderer);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
	}

	

	SDL_FreeSurface(surface);
	IMG_Quit();
	SDL_Quit();

	return 0;
}