//
//  Entity.h
//  RPG
//
//  Created by Ben Wenzel on 3/10/14.
//  Copyright (c) 2014 Ben Wenzel. All rights reserved.
//

#ifndef __RPG__Entity__
#define __RPG__Entity__

#include <iostream>
#include "Sprite.h"

class Entity
{
public:
	Entity();
	~Entity();
	void update(double time);
	void render(double time);
private:
	int m_hitpoints;
	double m_velocity;
	Sprite *sprite;
};

#endif /* defined(__RPG__Entity__) */
