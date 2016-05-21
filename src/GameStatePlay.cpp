//
//  GameStatePlay.cpp
//  RPG
//
//  Created by Ben Wenzel on 3/10/14.
//  Copyright (c) 2014 Ben Wenzel. All rights reserved.
//

#include "GameStatePlay.h"
#include "SharedResources.h"

GameStatePlay::GameStatePlay()
{

}


GameStatePlay::~GameStatePlay()
{

}


void GameStatePlay::update(double time)
{
	if (inputMan->pressing[DOWN])
	{
		printf("pressing right\n");
	}
}


void GameStatePlay::render(double time)
{

}
