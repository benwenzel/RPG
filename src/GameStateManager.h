//
//  GameStateManager.h
//  RPG
//
//  Created by Ben Wenzel on 3/10/14.
//  Copyright (c) 2014 Ben Wenzel. All rights reserved.
//

#ifndef __RPG__GameStateManager__
#define __RPG__GameStateManager__

#include <iostream>

#include "GameState.h"

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();
	
	void update(double time);
	void render(double time);
	
	GameState *currentState;
	bool done;
};

#endif /* defined(__RPG__GameStateManager__) */
