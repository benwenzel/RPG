#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <vector>
#include <string>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	
	SDL_Texture* getTexture(const std::string &imagepath);
	
private:
	SDL_Texture* loadTexture(const std::string &imagepath);
	
	std::vector<SDL_Texture*> textures;
	std::vector<std::string> names;
	int m_maxTextureWidth;
	int m_maxTextureHeight;
};

#endif
