#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"


class GameObject
{
public:
	GameObject(Camera& camera, Shader& shader, Model& model, glm::vec3 position, glm::vec3 velocity, float mass, 
		glm::vec3 torque = glm::vec3(0,0,0), float rotationAngle = 0, float angularVel = 0);
	void Move(GLfloat deltaTime);
	void Render();

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 torque;

	float rotationAngle;
	float angularVel;
	float mass;
	
private:
	Camera* camera;
	Model* model;
	Shader* shader;
};



#endif
