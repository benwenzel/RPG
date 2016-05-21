 //
//  main.cpp
//  RPG
//
//  Created by Ben Wenzel on 3/10/14.
//  Copyright (c) 2014 Ben Wenzel. All rights reserved.
//

#include <iostream>
#include <SDL.h>
#include "SharedResources.h"
#include "Settings.h"

void init()
{
	settings::loadSettings("data/settings.cfg");
	
	uint sdlFlags = SDL_INIT_VIDEO;	// <- SDL initialization flags
	if (SDL_Init(sdlFlags) < 0)
	{
		std::cerr << "Error: Failed to initialize SDL: " << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	uint winFlags = 0;	// <- SDL window flags
	window = SDL_CreateWindow("RPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, winFlags);
	if (window == NULL)
	{
		std::cerr << "Error: Failed to create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(-1);
	}
	
	//initialize the managers
	//note that the order of manager initialization/deletion is extremely strict in order to avoid segfaults
	inputMan = new InputManager();
	renderer = new Renderer();
	texMan = new TextureManager();
	gameMan = new GameStateManager();
}

void gameloop()
{
	double previous = SDL_GetTicks();
	double lag = 0.0;
	bool quit = false;
	
	while (!quit)
	{
		double now = SDL_GetTicks();	//the time at the beginning of the new game 'tick'
		double dt = now - previous;		//the amount of time it took for the last game tick to complete
		
		previous = now;
		lag += dt;	//add the duration of the last game tick ('delta time') to the lag
		
		quit = inputMan->processInput();
		
		while (lag >= MS_PER_UPDATE)	//as long as the lag is greater than the interval between updates, update as many times as necessary to catch up
		{
			//x+=VELOCITY*(MS_PER_UPDATE/1000);
			gameMan->update(MS_PER_UPDATE/1000);
			lag -= MS_PER_UPDATE;
		}		
		
		renderer->clearScreen();
		gameMan->render(lag/1000);
		renderer->swapBuffers();
		
		//SDL_RenderClear(renderer);
		//std::cout << "position before interpolation: " << x << std::endl;
		//renderTexture(image, renderer, x+(VELOCITY*(lag/1000)), y);
		//std::cout << "position after interpolation: " << x+(VELOCITY*(lag/1000)) << std::endl;
		//SDL_RenderPresent(renderer);
	}
}

void close()
{
	delete gameMan;
	gameMan = NULL;
	
	delete texMan;
	texMan = NULL;
	
	delete renderer;
	renderer = NULL;
	
	delete inputMan;
	inputMan = NULL;
	
	SDL_DestroyWindow(window);
	window = NULL;
	
	SDL_Quit();
}

int main(int argc, const char * argv[])
{
	init();
	gameloop();
	close();
	
    return 0;
}
