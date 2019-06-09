#include "BehaviourSystem.h"
#include "Entities.h"
#include "Position.h"

void BehaviourSystem::update() {
	for (Entities& e : Entities::getEntityList()) {
		if (e.getComponentMask() & componentMask == componentMask) {
			Position& position = e.getComponent<Position>();
		}
	}
}

BehaviourSystem::BehaviourSystem()
{
	componentMask = Position::getMask();
}


BehaviourSystem::~BehaviourSystem()
{

}
