#pragma once
#include "System.h"
class BehaviourSystem : System<BehaviourSystem>
{
public:
	BehaviourSystem();
	void update();
	~BehaviourSystem();
};

