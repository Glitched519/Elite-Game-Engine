#include "InputSystem.h"
#include "Engine.h"
#include "Events.h"
#include "InputEvent.h"
#include "SFML/graphics.hpp"
#include <math.h>

InputSystem::InputSystem() {
	componentMask = Position::getMask() | Sprite::getMask();
}

sf::Keyboard::Key& operator ++(sf::Keyboard::Key& e) {
	if (e == sf::Keyboard::KeyCount) {
		throw std::out_of_range("for Key operator ++");
	}
	e = sf::Keyboard::Key(static_cast<std::underlying_type<sf::Keyboard::Key>::type>(e) + 1);
}

void InputSystem::Update() {

	// Loop through all keys and emit event if one is pressed
	for (sf::Keyboard::Key e = sf::Keyboard::A; e != sf::Keyboard::KeyCount; ++e) {
		if (sf::Keyboard::isKeyPressed(e)) {
			Events<InputEvent>::emit(InputEvent(e));
		}
	}
}

InputSystem::~InputSystem(){
}


