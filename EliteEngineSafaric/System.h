#pragma once
#include <SFML/Graphics.hpp>
template <typename Derived>
class System
{
public:
	uint32_t componentMask;
	void Update() {
		static_cast <Derived>(this).Update();
	}
	//System();
	//~System();
};