/*
 *  Renderer.h
 *
 *  Licensed under the GPLv3+
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
//#include "Sprite.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	
	//void render(const Sprite *sprite) const;					// <- render a sprite
	void render(SDL_Texture *texture, int x=0, int y=0) const;	// <- directly render a texture at x,y (NB: is this method really necessary?)
	void clearScreen() const;
	void swapBuffers() const;

private:
	friend class TextureManager;	// <- so that TextureManager has access to Renderer's internal SDL_Renderer instance
	SDL_Renderer *m_SDLRenderer;
};

#endif
