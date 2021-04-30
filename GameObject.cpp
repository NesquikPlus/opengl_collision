#include "GameObject.h"

GameObject::GameObject(Camera& camera, Shader& shader, Model& model, glm::vec3 position, glm::vec3 velocity, float mass, glm::vec3 torque, float rotationAngle, float angularVel)
{
    this->camera = &camera;
    this->shader = &shader;
    this->model = &model;

    this->position = position;
    this->velocity = velocity;
    this->mass = mass;

    this->rotationAngle = rotationAngle;
    this->angularVel = angularVel;
    this->torque = torque;
}


void GameObject::Move(GLfloat deltaTime)
{
    this->position += this->velocity * deltaTime;
    this->rotationAngle += this->angularVel * deltaTime;
}


void GameObject::Render()
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, this->position);
    if (glm::length(torque) != 0)
        model = glm::rotate(model, rotationAngle, torque);

    shader->setMat4("model", model);
    this->model->Draw(*(this->shader));
}

