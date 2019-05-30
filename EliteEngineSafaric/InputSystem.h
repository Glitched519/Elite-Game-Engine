#pragma once
#include "Entities.h"
#include "System.h"
#include "Position.h"
#include "Sprite.h"
class InputSystem : System<InputSystem>
{
public:
	InputSystem();
	~InputSystem();
	void Update();

};

