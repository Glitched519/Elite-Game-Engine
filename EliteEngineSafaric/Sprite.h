#pragma once
#include <string.h>
#include "Component.h"
#include <SFML/Graphics.hpp>
class Sprite:public Component<Sprite>
{
public:
	sf::Sprite sprite;
	std::string Texture;
	int width, height;
	bool isOriginCenter;
	Sprite(void);
	void setPosition(int x, int y);
	~Sprite(void);
};

