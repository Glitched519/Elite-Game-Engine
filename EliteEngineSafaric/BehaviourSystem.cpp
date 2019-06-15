#include "BehaviourSystem.h"
#include "Entities.h"
#include "Position.h"

void BehaviourSystem::update() {
	for (Entities& e : Entities::getEntityList()) {
		if (e.getComponentMask() & componentMask == componentMask) {
			Position& position = e.getComponent<Position>();

			LuaTable global = lua.GetGlobalEnvironment();

			//Create a Lua Table from the Position Component
			LuaTable positionTable = lua.CreateTable();
			positionTable.Set("x", position.X);
			positionTable.Set("y", position.Y);

			//Put the Position Lua Table in the script's global score
			global.Set("position", positionTable);

			auto scriptUpdate = global.Get<LuaFunction<void(void)>>("update");

			//Run the script's update function
			scriptUpdate.Invoke();

			//Get the update osition Table from the global score
			LuaTable newPositionTable = global.Get<LuaTable>("position");

			//Update the in-engine Position Comment
			position.X = newPositionTable.Get<float>("x");
			position.Y = newPositionTable.Get<float>("y");
		}
	}
}

BehaviourSystem::BehaviourSystem(void)
{
	componentMask = Position::getMask();
	//Load Lua script
	scriptFile = "Debug/Assets/Scripts/AScript.lua";
	std::ifstream file(scriptFile);
	if (!file) {
		std::cerr << "Failed to open \"" << scriptFile << "\"" << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	scriptContents = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	lua.LoadStandardLibraries();
	//Run the script to check for errors
	std::string luaErrors = lua.RunScript(scriptContents);
	if (luaErrors != "No errors") {
		std::cerr << luaErrors << std::endl;
	}
}


BehaviourSystem::~BehaviourSystem()
{

}
