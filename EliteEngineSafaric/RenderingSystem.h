#pragma once
#include "iSystem.h"
#include "System.h"
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
class RenderingSystem : public System<RenderingSystem>
{
private:
	std::unordered_map<std::string, sf::Texture*> _textureMap;
	sf::Texture* _loadTexture(std::string Texture);

public:
	RenderingSystem(sf::RenderWindow* window);
	~RenderingSystem(void);
	void update(sf::RenderWindow * window);
};

