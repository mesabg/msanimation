#include <Batch/Camera.h>

// General main initializations
Camera* Camera::uniqueCamera = NULL;

Camera::Camera(vec3 position, vec3 up, GLfloat yaw, GLfloat pitch): position(position), up(up), pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
{
	this->updateVectors();
}

Camera::~Camera()
{
	// Do something
}

void Camera::updateVectors()
{
	// Calculate the new Front vector
	vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

Camera * Camera::instance(vec3 position, vec3 up, GLfloat yaw, GLfloat pitch)
{
	if (!uniqueCamera)
		uniqueCamera = new Camera(position, up, yaw, pitch);
	return uniqueCamera;
}

void Camera::destroy()
{
	if (!uniqueCamera) return;
	uniqueCamera->~Camera();
}

GLfloat Camera::getZoom()
{
	return this->zoom;
}

vec3 Camera::getPosition()
{
	return this->position;
}

vec3 Camera::getFront()
{
	return this->front;
}

mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::processKeyboard(CameraMovement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;

	if (direction == FORWARD)
	{
		this->position += this->front * velocity;
	}

	if (direction == BACKWARD)
	{
		this->position -= this->front * velocity;
	}

	if (direction == LEFT)
	{
		this->position -= this->right * velocity;
	}

	if (direction == RIGHT)
	{
		this->position += this->right * velocity;
	}
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	xOffset *= this->mouseSensitivity;
	yOffset *= this->mouseSensitivity;

	this->yaw += xOffset;
	this->pitch += yOffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (this->pitch > 89.0f)
		{
			this->pitch = 89.0f;
		}

		if (this->pitch < -89.0f)
		{
			this->pitch = -89.0f;
		}
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateVectors();
}

void Camera::processMouseScroll(GLfloat yOffset)
{
	// Do something
}
