#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
class Position:public Component<Position>
{
public:
	float X, Y;
	Position() : X(0.0f), Y(0.0f) {

	}

};