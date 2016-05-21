//
//  GameStateManager.cpp
//  RPG
//
//  Created by Ben Wenzel on 3/10/14.
//  Copyright (c) 2014 Ben Wenzel. All rights reserved.
//

#include "GameStateManager.h"
#include "GameStatePlay.h"

GameStateManager::GameStateManager()
{
	currentState = new GameStatePlay;	//go directly to the play state when the program starts
	done = false;
}


GameStateManager::~GameStateManager()
{
	delete currentState;
}


void GameStateManager::update(double time)
{
	//Is a new gamestate being requested?
	//If so, delete the old one before assigning the new one, otherwise we create a memory leak
	GameState *requestedState = currentState->getRequestedGameState();
	
	if (requestedState != NULL)
	{
		delete currentState;
		currentState = requestedState;
	}
	
	currentState->update(time);
	done = currentState->exitRequested;
}

void GameStateManager::render(double time)
{
	currentState->render(time);
}
