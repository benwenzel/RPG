#ifndef SHARED_RESOURCES_H
#define SHARED_RESOURCES_H

#include <SDL.h>
#include "Renderer.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "GameStateManager.h"
//#include "Camera.h"


extern SDL_Window *window;
extern Renderer *renderer;

extern InputManager *inputMan;
extern TextureManager *texMan;
extern GameStateManager *gameMan;

//extern Camera *camera;

#endif //SHARED_RESOURCES_H
