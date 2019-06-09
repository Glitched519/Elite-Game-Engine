#include "Engine.h" 
#include "Entities.h"
#include "Sprite.h"
#include "Position.h"
#include <iostream>
#include <string>
#include "Events.h"
#include "Delegate.h"
#include "InputEvent.h"
#include "InputSystem.h"
Engine &Engine::getInstance(void) {
	static Engine instance;
	return instance;
}

Engine::Engine(void):quit(false)
{
	renderingSystem = new RenderingSystem(window);
	inputSystem = new InputSystem();
	physicsSystem = new PhysicsSystem();
	behaviourSystem = new BehaviourSystem();
	camera = new Camera();
	physicsScale = 100.0f;
}


void Engine::start(void)
{
	int WIDTH = 1920;
	int HEIGHT = 1080;
	Scene::load("Debug/Assets/Scene.json");
	sf::RenderWindow win(sf::VideoMode(WIDTH, HEIGHT), "Game Engine", sf::Style::Fullscreen);
	sf::View cam;
	cam.setCenter(WIDTH/2, HEIGHT/2);
	cam.setSize(WIDTH,HEIGHT);
	camera->cameraView = &cam;
	window = &win;
	while (window->isOpen()) {
		update();
	}
}

void Engine::update() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
			quit = true;
		}
	}
	window->clear();
	window->setView(*camera->cameraView);
	inputSystem->Update();
	renderingSystem->update(window);
	physicsSystem->update();
	
	window->display();
	
}

Engine::~Engine(void)
{
	delete(renderingSystem);
	delete(physicsSystem);
	delete(inputSystem);
	delete(behaviourSystem);
}
