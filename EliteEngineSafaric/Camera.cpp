#include "Camera.h"



Camera::Camera()
{
	
}

void Camera::setCamera(float x, float y)
{
	cameraView->setCenter(sf::Vector2f(400.f,300.f));
}

void Camera::moveCamera(float x, float y)
{
	cameraView->move(x, y);
}

void Camera::zoomCamera(float factor)
{
	cameraView->zoom(factor);
}


Camera::~Camera()
{
}
