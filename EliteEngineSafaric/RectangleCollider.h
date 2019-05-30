//RectangleCollider.h
#pragma once
#include "Component.h"

class RectangleCollider : public Component< RectangleCollider >
{
public:
    RectangleCollider(void) : width( 1.0f ), height( 1.0f ) {};
    float width, height;
};