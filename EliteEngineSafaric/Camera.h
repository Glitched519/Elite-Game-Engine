#pragma once
#include "SFML/Graphics.hpp"
class Camera
{
public:
	Camera();
	void setCamera(float x, float y);
	void moveCamera(float x, float y);
	void zoomCamera(float factor);
	sf::View* cameraView;
	~Camera();
private:
	

};

