#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <unistd.h>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"


class GameObject
{
public:
	GameObject(string directory, glm::vec3 position, glm::vec3 velocity, float mass, 
		glm::vec3 torque = glm::vec3(0,0,0), float rotationAngle = 0, float angularVel = 0);

	void Move(GLfloat deltaTime);
	void Render();

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 size;

	glm::vec3 torque;
	float rotationAngle;
	float angularVel;
	float mass;

private:
	Model* model;
	Shader* shader;
	Camera* camera;
	friend class Game;
};




#endif