/*
 *  Settings.h
 *
 *  Licensed under the GPLv3+
 */

#include <string>
namespace settings
{
	void loadSettings(const std::string &filepath);
}

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern double MS_PER_UPDATE;	//update the physics 60 times per second

/*extern int TILE_WIDTH;
extern int TILE_HEIGHT;
extern int TILE_WIDTH_HALF;
extern int TILE_HEIGHT_HALF;*/
/*int screenWidth();
int screenHeight();
int maxFPS();
int maxFrameDuration();*/
