//
//  GameState.cpp
//  RPG
//
//  Created by Ben Wenzel on 3/10/14.
//  Copyright (c) 2014 Ben Wenzel. All rights reserved.
//

#include "GameState.h"

GameState::GameState() : requestedGameState(0), exitRequested(false)
{
	
}


GameState* GameState::getRequestedGameState()
{
	return requestedGameState;
}


GameState::~GameState()
{
	
}


void GameState::update(double time)
{
	
}


void GameState::render(double time)
{
	
}
