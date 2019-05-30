#pragma once
#include "Events.h"
#include "SFML/Graphics.hpp"
class InputEvent : public Events<InputEvent>
{
public:
	sf::Keyboard::Key keypressed;
	InputEvent(sf::Keyboard::Key key);
	~InputEvent();
};

