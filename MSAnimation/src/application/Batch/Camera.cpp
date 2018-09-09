#include <Batch/Camera.h>

// General main initializations
Camera* Camera::uniqueCamera = NULL;

Camera::Camera(vec3 position, GLfloat yaw, GLfloat pitch, GLfloat zoom) {
	//-- Default vectors
	this->position = position;
	this->up = vec3(0.0f, 1.0f, 0.0f);

	//-- Default variable values
	this->yaw = yaw;
	this->pitch = pitch;
	this->zoom = zoom;

	//-- Update
	this->updateVectors();
}

Camera::~Camera()
{
	// Do something
}

void Camera::updateVectors()
{
	// Calculate the new Front vector
	vec3 target;
	target.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	target.y = sin(glm::radians(this->pitch));
	target.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	//-- Update view matrix
	this->view = glm::lookAt(this->position, target, this->up);
}

Camera * Camera::instance(vec3 position, GLfloat yaw, GLfloat pitch, GLfloat zoom)
{
	if (!uniqueCamera)
		uniqueCamera = new Camera(position, yaw, pitch, zoom);
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

mat4 Camera::getViewMatrix()
{
	return this->view;
}

void Camera::processKeyboard(CameraMovement direction, GLfloat deltaTime)
{
	/*GLfloat velocity = this->movementSpeed * deltaTime;

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
	}*/
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
