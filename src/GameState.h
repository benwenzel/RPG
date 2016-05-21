//
//  GameState.h
//  RPG
//
//  Created by Ben Wenzel on 3/10/14.
//  Copyright (c) 2014 Ben Wenzel. All rights reserved.
//

#ifndef __RPG__GameState__
#define __RPG__GameState__

#include <iostream>

class GameState
{
protected:
	GameState *requestedGameState;
	
public:
	GameState();
	virtual ~GameState();
	
	virtual void update(double time);
	virtual void render(double time);
	GameState* getRequestedGameState();
	
	bool exitRequested;
};

#endif /* defined(__RPG__GameState__) */
