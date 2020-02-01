#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"


class GameObject
{
public:
	GameObject(string directory, glm::vec3 position, glm::vec3 velocity, float mass);

	void Move(GLfloat deltaTime);
	void Render();

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 size;

	glm::vec3 rotationLine;
	float angularVel;
	float rotationAngle;

	float mass;

private:
	Model* model;
	Shader* shader;
	Camera* camera;
	friend class Game;
};




#endif