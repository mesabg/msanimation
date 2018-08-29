#pragma once

// Global includes
#include <vector>
#define GLEW_STATIC
#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Local includes

// Using spaces
using std::vector;
using glm::vec3;
using glm::mat4;

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera {
private:
	static Camera* uniqueCamera;

	// Initializers
	Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
	~Camera();

	// Camera Attributes
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 worldUp;

	// Eular Angles
	GLfloat yaw;
	GLfloat pitch;

	// Camera options
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat zoom;

	// General functions
	void updateVectors();

public:
	// Get Instance
	static Camera* instance(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
	static void destroy();

	// Getters and setters
	GLfloat getZoom();
	vec3 getPosition();
	vec3 getFront();
	mat4 getViewMatrix();

	// Movement system
	void processKeyboard(CameraMovement direction, GLfloat deltaTime);
	void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
	void processMouseScroll(GLfloat yOffset);
};