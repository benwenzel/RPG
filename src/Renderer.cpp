/*
 *  Renderer.cpp
 *  SDL2 Template
 *
 *  Created by benjamin on 8/15/13.
 *  Copyright 2013 Ben Wenzel. All rights reserved.
 *
 */
#include <iostream>
#include "SharedResources.h"	//for r/w access to the external 'window' and 'renderer' variables
#include "Renderer.h"

Renderer::Renderer()
{
	m_SDLRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (m_SDLRenderer == NULL)
	{
		std::cerr << "Error: Failed to create SDL_Renderer: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(-1);
	}
	else
	{
		SDL_SetRenderDrawColor(m_SDLRenderer, 0, 0, 0, 0);
	}
}


Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_SDLRenderer);
}


/*void Renderer::render(const Sprite *sprite) const
{
	if (sprite == NULL)
	{
		//error here
	}
	else
	{
		//Renderer is a friend class of Sprite, so it has access the sprite's private members
		SDL_RenderCopyEx(m_SDLRenderer,
						 sprite->m_texture,
						 &sprite->m_texRect,
						 &sprite->m_bounds,
						 sprite->m_rotAngle,
						 &sprite->m_origin,
						 sprite->getFlip());
	}
}*/


void Renderer::render(SDL_Texture *texture, int x, int y) const
{
	SDL_RenderCopy(m_SDLRenderer, texture, NULL, NULL);
}


void Renderer::clearScreen() const
{
	SDL_RenderClear(m_SDLRenderer);
}


void Renderer::swapBuffers() const
{
	SDL_RenderPresent(m_SDLRenderer);
}
