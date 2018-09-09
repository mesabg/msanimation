#pragma once

// Global includes
#include <vector>
#define GLEW_STATIC
#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

// Local includes

// Using spaces
using std::vector;
using glm::vec3;
using glm::mat4;

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

// Default camera values
const GLfloat YAW = 0.0f;
const GLfloat PITCH = 30.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera {
private:
	static Camera* uniqueCamera;

	// Initializers
	Camera(vec3 position = vec3(0.0f, 0.0f, 20.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH, GLfloat zoom = ZOOM);
	~Camera();

	// View matrix
	mat4 view;

	// Camera Attributes
	vec3 position;
	vec3 up;

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
	static Camera* instance(vec3 position = vec3(0.0f, 0.0f, 20.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH, GLfloat zoom = ZOOM);
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