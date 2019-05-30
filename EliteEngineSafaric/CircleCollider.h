//CircleCollider.h
#pragma once
#include "Component.h"

class CircleCollider : public Component< CircleCollider > 
{
public:
    CircleCollider() : radius( 1.0f ) {};
    float radius;
};