//
//  Entity.cpp
//  RPG
//
//  Created by Ben Wenzel on 3/10/14.
//  Copyright (c) 2014 Ben Wenzel. All rights reserved.
//

#include "Entity.h"

Entity::Entity() : sprite(NULL)
{
	sprite = new Sprite;
}


Entity::~Entity()
{
	if (sprite != NULL)
	{
		delete sprite;
	}
}


void Entity::update(double time)
{
	sprite->update(time);
}


void Entity::render(double time)
{
	sprite->render(time);
}
