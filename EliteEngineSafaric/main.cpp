#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "InputEvent.h"
#include "Entities.h"
#include <iostream>

void onButtonPressed(InputEvent);

int main(int argc, char *args[]) {
	Engine& engine = Engine::getInstance();
	Events<InputEvent>::addListener<&onButtonPressed>();
	engine.start();
	
	return EXIT_SUCCESS;
}

void onButtonPressed(InputEvent e) {
	int componentMask = Position::getMask() | Sprite::getMask();
	for (Entities& entity : Entities::getEntityList()) {
		if ((entity.getComponentMask() & componentMask) == componentMask) {
			Position& position = entity.getComponent<Position>();
			switch (e.keypressed) {
			case sf::Keyboard::W:
				Engine::getInstance().camera->moveCamera(0, -0.05f);
				break;
			case sf::Keyboard::A:
				Engine::getInstance().camera->moveCamera(-0.05f, 0);
				break;
			case sf::Keyboard::S:
				Engine::getInstance().camera->moveCamera(0, 0.05f);
				break;
			case sf::Keyboard::D:
				Engine::getInstance().camera->moveCamera(0.05f, 0);
				break;
			case sf::Keyboard::Q:
				Engine::getInstance().camera->zoomCamera(1.0001f);
				break;
			case sf::Keyboard::E:
				Engine::getInstance().camera->zoomCamera(0.9999f);
				break;
			}
			if (entity.getComponentMask() & Rigidbody::getMask == Rigidbody::getMask) {
				Rigidbody &rb = entity.getComponent<Rigidbody>();
				switch (e.keypressed) {
				case sf::Keyboard::Up:
					rb.xForce = 0;
					rb.yForce = -2;
					break;
				case sf::Keyboard::Down:
					rb.xForce = 0;
					rb.yForce = 2;
					break;
				case sf::Keyboard::Left:
					rb.xForce = -2;
					rb.yForce = 0;
					rb.rotationAngle -= 10 * b2_pi / 180.0f;
					break;
				case sf::Keyboard::Right:
					rb.xForce = 2;
					rb.yForce = 0;
					rb.rotationAngle += 10 * b2_pi / 180.0f;
					break;
				default:
					rb.xForce = 0;
					rb.yForce = 0;
					break;
					}
				}
			}
		}
	}