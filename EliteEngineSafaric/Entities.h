#pragma once
#include <SFML/Graphics.hpp>
#include<type_traits>
#include <cassert>
#include <vector>
#include "Component.h"

class Entities
{
private:
	Entities();
	Entities(size_t ID);
	size_t _ID;
	uint32_t _componentMask;
	static std::vector<Entities> _entityList;
public:
	uint32_t getComponentMask();
	
	template <typename C> 
	C&addComponent() {
		static_assert (
			std::is_base_of<Component<C>, C>::value, "Error: Can only add component to certain entities.");
		_componentMask = _componentMask | C::getMask();
		C& component = getComponent<C>();
		return component;
	}

	template <typename C>
	C&getComponent() {
		static_assert( std::is_base_of<Component<C>, C>::value, "Error. You can only get component types from entities." );
		return C::getComponentEntityWithID(_ID);
	}
	
	size_t getID();
	static std::vector<Entities>&getEntityList();
	static Entities&create();
};

