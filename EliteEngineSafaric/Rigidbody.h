#pragma once

#include "Component.h"

class Rigidbody : public Component<Rigidbody>
{
public:
	float xForce;
	float yForce;
	float rotationAngle;
	float torqueForce;
	Rigidbody();
	~Rigidbody();
};

