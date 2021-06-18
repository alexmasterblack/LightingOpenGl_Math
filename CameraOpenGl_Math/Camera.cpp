#include "Camera.h"

#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

float Radians(float number) {
	return number * static_cast<float>(0.01745329251994329576923690768489);
}

Camera::Camera()
{
	// позиция камеры
	// x - камера сдвигается вправо, картинка влево y - камера поднимается вверх, картинка вниз, z - чем больше, тем дальше камера
	positionCamera = Vec3(0.0f, 0.0f, 3.0f);
	// позиция цели
	frontCamera = Vec3(0.0f, 0.0f, -1.0f);
	// вектор вверх
	upCamera = Vec3(0.0f, 1.0f, 0.0f);
	// вверх - вниз
	pitch = 0.0f;
	// поворот вправо - влево
	yaw = -90.0f;
}

Mat4 Camera::GetViewMatrix()
{
	Mat4 result;
	return result.LookAt(positionCamera, positionCamera + frontCamera, upCamera);
}

Mat4 Camera::GetProjectionMatrix()
{
	// поле обзора, соотношение сторон, ближняя и дальняя плоскость усечения пирамиды
	Mat4 result;
	return result.Perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);
}

void Camera::ReadInput()
{
	// вперед, приближение к цели
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		positionCamera += frontCamera * speed;
	}
	// влево, векторное произведение дает перпендикуляр
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Vec3 crossResult(frontCamera.CrossProduct(upCamera));
		positionCamera -= crossResult.Normalize() * speed;
	}
	// вправо
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Vec3 crossResult(frontCamera.CrossProduct(upCamera));
		positionCamera += crossResult.Normalize() * speed;
	}
	// вниз, отдаление от цели
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		positionCamera -= frontCamera * speed;
	}
}

void Camera::MouseInput(sf::Window& window)
{
	// смещение с прошлого положения мыши
	float xOffset = sf::Mouse::getPosition(window).x - xPos;
	float yOffset = yPos - sf::Mouse::getPosition(window).y;
	xPos = sf::Mouse::getPosition(window).x;
	yPos = sf::Mouse::getPosition(window).y;

	yaw += (xOffset * 0.3f);
	pitch += (yOffset * 0.3f);

	Vec3 front;
	front.x = cos(Radians(yaw)) * cos(Radians(pitch));
	front.y = sin(Radians(pitch));
	front.z = sin(Radians(yaw)) * cos(Radians(pitch));
	frontCamera = front.Normalize();
}

Vec3 Camera::GetPosition()
{
	return positionCamera;
}

Vec3 Camera::GetFront()
{
	return frontCamera;
}
