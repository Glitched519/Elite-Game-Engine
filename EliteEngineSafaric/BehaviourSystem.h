#pragma once
#include <fstream>
#include <iostream>
#include "luacppinterface.h"
#include "System.h"

class BehaviourSystem : System<BehaviourSystem>
{
public:
	BehaviourSystem();
	void update();
	~BehaviourSystem();

private:
	Lua lua;
	std::string scriptFile;
	std::string scriptContents;
};

