#include <iostream>
#include <algorithm>	//for find()
#include <SDL_image.h>
#include "SharedResources.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
	//initialize SDL_image here
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!IMG_Init(imgFlags))
	{
		printf("Error: Failed to initialize SDL_image: %s\n", IMG_GetError());
	}
	
	//get the maximum texture dimensions for the system
	SDL_RendererInfo ri;
	SDL_GetRendererInfo(renderer->m_SDLRenderer, &ri);
	m_maxTextureWidth = ri.max_texture_width;
	m_maxTextureHeight = ri.max_texture_height;
#ifdef DEBUG
	std::cout << "Maximum supported texture dimensions: " << m_maxTextureWidth << "x" << m_maxTextureHeight << std::endl;
#endif
}


TextureManager::~TextureManager()
{
	int backIndex = textures.size() - 1;
	while (backIndex >= 0)
	{
		if (textures[backIndex] != NULL)
		{
			SDL_DestroyTexture(textures[backIndex]);
			textures.erase(textures.begin()+backIndex);
			names.erase(names.begin()+backIndex);
		}
		--backIndex;
	}
	IMG_Quit();
}


SDL_Texture* TextureManager::getTexture(const std::string &imagepath)
{
	//std::cout << "Getting texture '" << imagepath << "'...\n";
	std::vector<std::string>::iterator found = find(names.begin(), names.end(), imagepath);
	if (found != names.end())
	{
		//std::cout << "That texture already exists\n";
		int index = distance(names.begin(), found);
		return textures[index];	
	}
	else
	{
		//std::cout << "That texture DOES NOT exist yet; creating it now...\n";
		SDL_Texture *tex = loadTexture(imagepath);
		textures.push_back(tex);
		names.push_back(imagepath);
		return textures.back();
	}
}


//TODO: Check to make sure that the surface is a power of two and that it doesn't exceed the max_texture_size
SDL_Texture* TextureManager::loadTexture(const std::string &imagepath)
{
	SDL_Texture* texture = NULL;
	
	SDL_Surface* surface = IMG_Load(("data/images/" + imagepath).c_str());
	if (surface == NULL)
	{
		std::cerr << "Error: Failed to load image '" << imagepath << "': " << IMG_GetError() << std::endl;
	}
	else
	{
		//this is the way we should be doing this operation?
		//texture = IMG_LoadTexture(renderer->m_SDLRenderer, imagepath.c_str());
        texture = SDL_CreateTextureFromSurface(renderer->m_SDLRenderer, surface);
		if (texture == NULL)
		{
			std::cerr << "Error: Failed to create texture from image '" << imagepath << "': " << IMG_GetError() << std::endl;
		}
		
		SDL_FreeSurface(surface);
	}
	
	return texture;
}
