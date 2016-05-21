//
//  GameStatePlay.h
//  RPG
//
//  Created by Ben Wenzel on 3/10/14.
//  Copyright (c) 2014 Ben Wenzel. All rights reserved.
//

#ifndef __RPG__GameStatePlay__
#define __RPG__GameStatePlay__

#include <iostream>
#include "GameState.h"

class GameStatePlay : public GameState
{
public:
	GameStatePlay();
	~GameStatePlay();
	
	void update(double time);
	void render(double time);
	
};

#endif /* defined(__RPG__GameStatePlay__) */
