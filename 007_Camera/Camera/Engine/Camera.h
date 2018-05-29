#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum class CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
private:
	// Default camera values
	static constexpr float YAW = -90.0f;
	static constexpr float PITCH = 0.0f;
	static constexpr float SPEED = 10.0f;
	static constexpr float SENSITIVITY = 0.1f;
	static constexpr float FOV = 45.0f;

public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	
	// Euler Angles
	float Yaw;
	float Pitch;
	
	float MovementSpeed;
	float MouseSensitivity;
	float Fov;

	Camera(int windowsWidth, int windowsHeight, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(int windowsWidth, int windowsHeight, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	void ProcessKeyboard(CameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);
	void UpdateWindowsSize(int windowsWidth, int windowsHeight);

	void UpdateCameraVectors();

	int m_windowsWidth;
	int m_windowsHeight;
};