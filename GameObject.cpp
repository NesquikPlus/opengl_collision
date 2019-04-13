#include "GameObject.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLuint screenWidth = 1600;
const GLuint screenHeight = 900;

GameObject::GameObject(string directory, glm::vec3 position, glm::vec3 velocity, float mass)
{
	this->position = position;
	this->velocity = velocity;
	this->shader = new Shader("shaders/shader.vs", "shaders/shader.fs");
	this->model = new Model(&directory[0]);
    this->mass = mass;
}


void GameObject::Move(GLfloat deltaTime)
{
	this->position += this->velocity * deltaTime;
}



void GameObject::Render()
{
	shader->Use();


    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

    // Draw the loaded model
    glm::mat4 mat;
    mat = glm::translate(mat, this->position); 
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(mat));
    

	this->model->Render(*(this->shader));
}


