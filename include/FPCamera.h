#ifndef FPCAMERA_H
#define FPCAMERA_H
#include "stdafx.h"
class FPCamera
{
public:
	enum class Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	static const float YAW;
	static const float PITCH;
	static const float SPEED;
	static const float SENSITIVITY;
	static const float ZOOM;
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true) noexcept;
	void ProcessMouseScroll(float yOffset) noexcept;
	void ProcessKeyboard(FPCamera::Movement direction, float deltaTime);
	glm::mat4 GetViewMatrix() const noexcept;

private:
	void UpdateCameraVectors() noexcept;
public:
	FPCamera(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f), float yaw=YAW, float pitch=PITCH);
	FPCamera();
	~FPCamera();
};
#endif
