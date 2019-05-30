#pragma once
#include "iShape.h"
class Rectangle : iShape
{
public:
	float width, height;
	float getArea() {
		return width * height;
	}
	Rectangle();
	~Rectangle();
};

