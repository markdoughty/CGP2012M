#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
public:
	GLfloat camZPos;
	GLfloat camXPos;
	GLfloat camYPos;
	GLfloat camXTarget;
	GLfloat camYTarget;
	GLfloat camZTarget;
	float camSpeed;

	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;

	glm::mat4 viewMatrix;

	//default constructor
	Camera()
	{
		//set camera position and what its looking at(the target)
		camXPos = 0.0f;
		camYPos = 0.0f;
		camZPos = 4.0f;
		camXTarget = 0.0f;
		camYTarget = 0.0f;
		camZTarget = 0.0f;
		camSpeed = 0.2;

		//set camera vectors
		cameraPosition = glm::vec3(camXPos, camYPos, camZPos);
		cameraTarget = glm::vec3(camXTarget, camYTarget, camZTarget);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		//create camera view matrix
		//the 'lookAt' function
		//specify the position, target and up vector of the camera
		//position: 0,0,4   Target: 0,0,0   up: y axis
		viewMatrix = glm::lookAt(cameraPosition, glm::normalize(cameraPosition - cameraTarget), cameraUp);
	}

	void updateCamera()
	{
		cameraPosition = glm::vec3(camXPos, camYPos, camZPos);
		cameraTarget = glm::vec3(camXTarget, camYTarget, camZTarget);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}

};