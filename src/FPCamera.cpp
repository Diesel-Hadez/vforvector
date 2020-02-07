//Largely thanks to learnopengl.com
#include "stdafx.h"
#include "FPCamera.h"

const float FPCamera::YAW = -90.0f;
const float FPCamera::PITCH = 0.0f;
const float FPCamera::SPEED = 2.5f;
const float FPCamera::SENSITIVITY = 0.1f;
const float FPCamera::ZOOM = 45.0f;


void FPCamera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) noexcept
{
	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	UpdateCameraVectors();
}

void FPCamera::ProcessMouseScroll(float yOffset) noexcept
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yOffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void FPCamera::ProcessKeyboard(FPCamera::Movement direction, float deltaTime)
{
	float velocity = MovementSpeed*deltaTime;
	if (direction == Movement::FORWARD)
		Position += Front * velocity;
	else if (direction == Movement::BACKWARD)
		Position -= Front * velocity;
	else if (direction == Movement::LEFT)
		Position -= Right * velocity;
	else if (direction == Movement::RIGHT)
		Position += Right * velocity;
	else if (direction == Movement::UP)
		Position += WorldUp * velocity;
	else if (direction == Movement::DOWN)
		Position -= WorldUp * velocity;
}

glm::mat4 FPCamera::GetViewMatrix() const noexcept
{
	return glm::lookAt(Position, Position + Front, Up);
}

void FPCamera::UpdateCameraVectors() noexcept
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

FPCamera::FPCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
MovementSpeed(SPEED), 
MouseSensitivity(SENSITIVITY), 
Zoom(ZOOM),
Position(position),
WorldUp(up),
Yaw(yaw),
Pitch(pitch)
{
	UpdateCameraVectors();
}

FPCamera::FPCamera()
{
}


FPCamera::~FPCamera()
{
}
