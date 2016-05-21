/*
 *  Settings.cpp
 *  SDL2 Template
 *
 *  Created by benjamin on 8/16/13.
 *  Copyright 2013 Ben Wenzel. All rights reserved.
 *
 */

#include "FileParser.h"
#include "Settings.h"
#include "UtilsParsing.h"

//loads settings from a configuration file
void settings::loadSettings(const std::string &filepath)
{
	printf("loading settings\n");
	FileParser fp;
	
	fp.open(filepath);
	while (fp.notEOF())
	{
		if (fp.isTag())
		{
			fp.parseTag();
		}
		else if (fp.isKeypair())
		{
			fp.parseKeypair();
			if (fp.isChildOf("[settings]"))
			{
				if (fp.key() == "screen_width")
				{
					SCREEN_WIDTH = toInt(fp.value());
				}
				else if (fp.key() == "screen_height")
				{
					SCREEN_HEIGHT = toInt(fp.value());
				}
				else if (fp.key() == "fullscreen")
				{
					
				}
				else
				{
					fp.invalidKeypair();
				}
			}
			else
			{
				fp.invalidKeypair();
			}
		}
		else //this is not a tag or keypair
		{
			fp.invalidLine();
		}
	}
	fp.close();
	
	//make sure the screen dimensions are greater than zero
	if (SCREEN_WIDTH <= 0) {
		SCREEN_WIDTH = 1024;
	}
	if (SCREEN_HEIGHT <= 0) {
		SCREEN_HEIGHT = 768;
	}
	
	// make sure to check if FULLSCREEN was already set from the --fullscreen CL argument so we don't override it
	
	return;
}

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
double MS_PER_UPDATE = 1000/60;	//update the physics 60 times per second

/*int TILE_WIDTH = 128;
int TILE_HEIGHT = 64;
int TILE_WIDTH_HALF = TILE_WIDTH/2;
int TILE_HEIGHT_HALF = TILE_HEIGHT/2;*/
