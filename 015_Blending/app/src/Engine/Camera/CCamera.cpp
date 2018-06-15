#include <Engine/Camera/CCamera.h>

#include <Engine/Shader/CShader.h>

// Constructor with vectors
CCamera::CCamera(int windowsWidth, int windowsHeight, glm::vec3 position, glm::vec3 up, float yaw, float pitch) : m_windowsWidth(windowsWidth), m_windowsHeight(windowsHeight), Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}
// Constructor with scalar values
CCamera::CCamera(int windowsWidth, int windowsHeight, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : m_windowsWidth(windowsWidth), m_windowsHeight(windowsHeight), Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}

void CCamera::Use(CShader& shader) const
{
	shader.SetMat4("view", GetViewMatrix());
	shader.SetMat4("projection", GetProjectionMatrix());

	shader.SetVec3("viewPos", GetPosition());
}

glm::mat4 CCamera::GetViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 CCamera::GetProjectionMatrix() const
{
	return glm::perspective(glm::radians(Fov), (float)m_windowsWidth / (float)m_windowsHeight, 0.1f, 100.0f);
}

glm::vec3 CCamera::GetPosition() const
{
	return Position;
}

glm::vec3 CCamera::GetFront() const
{
	return Front;
}

void CCamera::ProcessKeyboard(ECameraMovement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == ECameraMovement::FORWARD)
		Position += Front * velocity;
	if (direction == ECameraMovement::BACKWARD)
		Position -= Front * velocity;
	if (direction == ECameraMovement::LEFT)
		Position -= Right * velocity;
	if (direction == ECameraMovement::RIGHT)
		Position += Right * velocity;
	if (direction == ECameraMovement::UP)
		Position += Up * velocity;
	if (direction == ECameraMovement::DOWN)
		Position -= Up * velocity;
}

void CCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch -= yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void CCamera::ProcessMouseScroll(float yoffset)
{
	if (Fov >= 1.0f && Fov <= 45.0f)
		Fov -= yoffset;
	if (Fov <= 1.0f)
		Fov = 1.0f;
	if (Fov >= 45.0f)
		Fov = 45.0f;
}

void CCamera::UpdateWindowsSize(int windowsWidth, int windowsHeight)
{
	m_windowsWidth = windowsWidth;
	m_windowsHeight = windowsHeight;
}

void CCamera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}
