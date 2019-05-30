#pragma once
#include "System.h"

#include <unordered_map>
#include <chrono>
#include <Box2D/Box2D.h>

#include "Entities.h"
#include "Position.h"
#include "Rigidbody.h"

using namespace std::chrono;

class PhysicsSystem : public System<PhysicsSystem>
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	float timeStep;
	int velocityIterations;
	int positionIterations;

	void update();
private:
	b2Vec2 _gravity;
	b2World * _world;

	time_point<system_clock> _lasWorldStepTime;

	std::unordered_map<size_t, b2Body* > _bodies;

	b2Body* createBody(size_t entityID, Position& position, float physicsScale);

};

