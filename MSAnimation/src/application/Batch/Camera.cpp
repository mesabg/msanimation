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

	//-- Move around
	this->mouseSensitivity = 0.1f;
	this->movementSpeed = 0.1f;
	this->distanceFromTarget = 20.0f;
	this->targetPosition = vec3(0.0f);
	this->angleAroundTarget = 0.0f;

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

void Camera::calculateZoom(GLfloat yOffset)
{
	float zoomLevel = yOffset * 0.1f;
	this->distanceFromTarget -= zoomLevel;
}

void Camera::calculatePitch(GLfloat deltaTime)
{
	float pitchChange = deltaTime;
	this->pitch -= pitchChange;
}

float Camera::calculateHorizontalDistance()
{
	return (float)(this->distanceFromTarget * glm::cos(glm::radians(this->pitch)));
}

float Camera::calculateVerticalDistance()
{
	return (float)(this->distanceFromTarget * glm::sin(glm::radians(this->pitch)));
}

void Camera::calculateCameraPosition(float horizontalDistance, float verticalDistance)
{
	float theta = this->angleAroundTarget;
	float offsetX = (float) horizontalDistance * glm::sin(glm::radians(theta));
	float offsetZ = (float) horizontalDistance * glm::cos(glm::radians(theta));
	this->position.x = this->targetPosition.x - offsetX;
	this->position.y = this->targetPosition.y + verticalDistance;
	this->position.z = this->targetPosition.z - offsetZ;
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
	GLfloat delta = deltaTime;

	//-- Calculate vertex
	if (direction == FORWARD) delta = -1 * deltaTime;
	if (direction == BACKWARD) delta = deltaTime;
	if (direction == LEFT) delta = -1 * deltaTime;
	if (direction == RIGHT) delta = deltaTime;

	//-- Calculate vertex
	this->calculatePitch(delta);
	float horizontalDistance = this->calculateHorizontalDistance();
	float verticalDistance = this->calculateVerticalDistance();
	this->calculateCameraPosition(horizontalDistance, verticalDistance);
	this->yaw = 180 - (0.0f + this->angleAroundTarget);
	this->updateVectors();
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	/*xOffset *= this->mouseSensitivity;
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
	this->updateVectors();*/
}

void Camera::processMouseScroll(GLfloat yOffset)
{
	// Do something
}
