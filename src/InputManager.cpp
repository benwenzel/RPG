#include <SFML/Window.hpp>

#include "SharedResources.h"
#include "InputManager.h"

InputManager::InputManager()
{
	for (int i=0; i<KEYCOUNT; i++)
	{
		pressing[i]=false;
		locked[i]=false;
	}
	
	SDL_GetMouseState(&mouse.x, &mouse.y);	
	done = false;
}


InputManager::~InputManager()
{
	
}


bool InputManager::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				return true;
				break;
			}
			case SDL_MOUSEMOTION:
			{
				SDL_GetMouseState(&mouse.x, &mouse.y);	//update the cursor coordinates whenever the mouse moves
				//printf("%f,%f\n", isoCoords.x, isoCoords.y);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:					
						//isoCoords = screenToIso(static_cast<Point>(mouse));
						//currentTile = tileAtScreen(mouse.x, mouse.y);
						//printf("Iso Coords: %f,%f\tTile Clicked: %f,%f\n", isoCoords.x, isoCoords.y, currentTile.x, currentTile.y);
						
						pressing[LMB] = true;
						locked[LMB] = true;
						break;
					case SDL_BUTTON_RIGHT:
						pressing[RMB] = true;
						locked[RMB] = true;
						break;
					default:
						break;
				}
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						pressing[LMB] = false;
						locked[LMB] = false;
						break;
					case SDL_BUTTON_RIGHT:
						pressing[RMB] = false;
						locked[RMB] = true;
						break;
					default:
						break;
				}
				break;
			}
			case SDL_KEYDOWN:
			{
				if (event.key.repeat == 0)	// <- don't process key repeats
				{
					{
						switch (event.key.keysym.sym)
						{
							case SDLK_UP:
								pressing[UP] = true;
								break;
							case SDLK_DOWN:
								pressing[DOWN] = true;
								break;
							case SDLK_LEFT:
								pressing[LEFT] = true;
								break;
							case SDLK_RIGHT:
								pressing[RIGHT] = true;
								break;
							default:
								break;								
						}
					}
				}
				break;
			}
			case SDL_KEYUP:
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						pressing[UP] = false;
						break;
					case SDLK_DOWN:
						pressing[DOWN] = false;
						break;
					case SDLK_LEFT:
						pressing[LEFT] = false;
						break;
					case SDLK_RIGHT:
						pressing[RIGHT] = false;
						break;
					default:
						break;								
				}
			}
			default:
				break;
		}
	}
	return false;
}
