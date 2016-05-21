//
//  Sprite.h
//  RPG
//
//  Created by Ben Wenzel on 3/13/14.
//  Copyright (c) 2014 Ben Wenzel. All rights reserved.
//

#ifndef __RPG__Sprite__
#define __RPG__Sprite__

#include <iostream>
#include <SDL.h>

class Sprite
{
public:
	Sprite();
	~Sprite();
	void update(double time);
	void render(double time);
private:
	friend class Renderer;	// <- so that Renderer has access to the memory addresses of Sprite's private members
	SDL_Texture *m_texture;	// <- the Sprite's current texture
};

#endif /* defined(__RPG__Sprite__) */
