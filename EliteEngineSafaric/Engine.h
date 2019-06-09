#pragma once
#include <SFML/Graphics.hpp>
#include "RenderingSystem.h"
#include "BehaviourSystem.h"
#include "Scene.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "Camera.h"

class PhysicsSystem;

class Engine
{
private:
	sf::RenderWindow* window;
	bool quit = false;
	RenderingSystem* renderingSystem;
	InputSystem* inputSystem;
	PhysicsSystem* physicsSystem;
	BehaviourSystem* behaviourSystem;
	
	Engine(void);
	~Engine(void);
	Engine(Engine &copy);
	Engine(Engine &&other);
	Engine &operator = (Engine &copy);

public:
	static Engine &getInstance(void);
	Camera* camera;
	void update();
	void start(void);
	float physicsScale;
	template <typename C>
	void addComponent() {

	}

	template <typename C>
	void removeComponent() {

	}

};

