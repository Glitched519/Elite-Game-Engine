#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
class BaseComponent {
protected:
	static uint32_t _componentTypeCount;
};
template <typename Derived>
class Component:public BaseComponent
{
public:
	//Component();
	static uint32_t getMask() {
		static uint32_t _mask = 1 << _componentTypeCount++;
		return _mask;
	};
	//~Component();

private:
	friend class Entities;
	static std::unordered_map<uint32_t, Derived>componentMap;

	static Derived& addComponentEntityWithID(uint32_t entityID) {
		Derived newComponent;
		componentMap[entityID] = newComponent;
		return componentMap[entityID]; 
	}
	static Derived& getComponentEntityWithID(uint32_t entityID) {
		return componentMap[entityID];
	}

};

template <typename Derived> 
std::unordered_map<uint32_t, Derived> Component<Derived>::componentMap;
