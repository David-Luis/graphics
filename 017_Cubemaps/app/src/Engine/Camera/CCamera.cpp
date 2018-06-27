#include <Engine/Camera/CCamera.h>

#include <Engine/Shader/CShader.h>
#include <Engine/Serialization/SerializationUtils.h>

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

void CCamera::UseForSkybox(CShader& shader) const
{
	shader.SetMat4("view", glm::mat4(glm::mat3(GetViewMatrix())));
	shader.SetMat4("projection", GetProjectionMatrix());
}

glm::mat4 CCamera::GetViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 CCamera::GetProjectionMatrix() const
{
	return glm::perspective(glm::radians(Fov), (float)m_windowsWidth / (float)m_windowsHeight, 0.1f, 100.0f);
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

void CCamera::SetPosition(glm::vec3 position)
{
	Position = position;
}

glm::vec3 CCamera::GetPosition() const
{
	return Position;
}

void CCamera::SetFront(glm::vec3 front)
{
	Front = front;
	UpdateCameraVectors();
}

glm::vec3 CCamera::GetFront() const
{
	return Front;
}

void CCamera::SetUp(glm::vec3 up)
{
	Up = up;
	UpdateCameraVectors();
}

glm::vec3 CCamera::GetUp() const
{
	return Up;
}

void CCamera::SetRight(glm::vec3 right)
{
	Right = right;
	UpdateCameraVectors();
}

glm::vec3 CCamera::GetRight() const
{
	return Right;
}

void CCamera::SetMovementSpeed(float movementSpeed)
{
	MovementSpeed = movementSpeed;
}

float CCamera::GetMovementSpeed() const
{
	return MovementSpeed;
}

void CCamera::SetMouseSensitivity(float mouseSensivity)
{
	MouseSensitivity = mouseSensivity;
}

float CCamera::GetMouseSensivity() const
{
	return MouseSensitivity;
}

void CCamera::SetFov(float fov)
{
	Fov = fov;
}

float CCamera::GetFov() const
{
	return Fov;
}

nlohmann::json CCamera::ToJson() const
{
	using json = nlohmann::json;

	json j;

	j["position"] = SerializationUtils::SerializeVec3(Position);
	j["yaw"] = Yaw;
	j["pitch"] = Pitch;
	j["up"] = SerializationUtils::SerializeVec3(Up);

	return j;
}

void CCamera::FromJson(const nlohmann::json& j)
{
	SetPosition(SerializationUtils::DeserializeVec3(j["position"]));
	Yaw = j["yaw"];
	Pitch = j["pitch"];
	SetUp(SerializationUtils::DeserializeVec3(j["up"]));
}
