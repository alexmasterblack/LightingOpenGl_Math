#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

#include <SFML/Window.hpp>

class Camera {
public:
	Camera();

	Mat4 GetViewMatrix();

	Mat4 GetProjectionMatrix();

	void ReadInput();

	void MouseInput(sf::Window&);

	Vec3 GetPosition();

	Vec3 GetFront();
private:
	// позиция камеры
	Vec3 positionCamera;
	Vec3 frontCamera;
	Vec3 upCamera;
	// скорость камеры
	float speed = 0.05f;
	// углы эйлера
	float yaw;
	float pitch;
	// координаты мыши
	float xPos = 800 / 2.0f;
	float yPos = 600 / 2.0f;
	// движение мышью в первый раз 
	bool mouseMove = true;
};

#endif