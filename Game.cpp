#include "Game.h"
#include "GameObject.h"

#include <iostream>
#include <cmath>
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/projection.hpp>

Game::Game()
{
}

void Game::updatePositions(GLfloat deltaTime)
{
	for (int i = 0; i < ballList.size(); i++)
	{
		GameObject& obj = *ballList[i];

		if (obj.position.x > 3.5f && obj.velocity.x > 0)
			obj.velocity.x *= -1;
		else if (obj.position.x < -3.5f && obj.velocity.x < 0)
			obj.velocity.x *= -1;

		if (obj.position.y > 3.5f && obj.velocity.y > 0)
			obj.velocity.y *= -1;
		else if (obj.position.y < -3.5f && obj.velocity.y < 0)
			obj.velocity.y *= -1;

		if (obj.position.z > 3.5f && obj.velocity.z > 0)
			obj.velocity.z *= -1;
		else if (obj.position.z < -3.5f && obj.velocity.z < 0)
			obj.velocity.z *= -1;


		obj.Move(deltaTime);
	}

	for (int i = 0; i < ballList.size(); i++)
	{
		for (int j = i + 1; j < ballList.size(); j++)
		{
			performCollision(i, j);
		}
	}
}

void Game::addShaderGroup(ShaderGroup shaderGroup)
{
	shaderGroups.push_back(shaderGroup);
}


void Game::performCollision(int obj1Num, int obj2Num)
{
	GameObject& obj1 = *ballList[obj1Num];
	GameObject& obj2 = *ballList[obj2Num];

	if (checkCollision(obj1, obj2) == true)
	{
		glm::vec3 centersVector = (obj1.position - obj2.position);
		centersVector = glm::normalize(centersVector);

		glm::vec3 v1proj = glm::proj(obj1.velocity, centersVector);
		glm::vec3 v2proj = glm::proj(obj2.velocity, centersVector);

		float v1n = -1.0f * glm::length(v1proj);
		float v2n = glm::length(v2proj);

		float v1n_final = (v1n * (obj1.mass - obj2.mass) + 2 * (obj2.mass) * v2n) / (obj1.mass + obj2.mass);
		float v2n_final = (v2n * (obj2.mass - obj1.mass) + 2 * (obj1.mass) * v1n) / (obj1.mass + obj2.mass);

		glm::vec3 Ff1_dir = glm::normalize(-(obj1.velocity - v1proj));
		glm::vec3 Ff2_dir = glm::normalize(-(obj2.velocity - v2proj));

		obj1.velocity = (obj1.velocity - v1proj) + (v1n_final * glm::normalize(centersVector));
		obj2.velocity = (obj2.velocity - v2proj) + (v2n_final * glm::normalize(centersVector));

		//Ff = kfc * (m * (deltav)/(deltat))
		float kfc_div_deltat = 0.1f;
		float Ff_norm = obj1.mass * (v1n_final - v1n) * kfc_div_deltat * 2;//equals to obj2.mass * (v2n_final - v2n) * kfc_div_deltat

		glm::vec3 Ff1 = Ff1_dir * Ff_norm;
		glm::vec3 Ff2 = Ff2_dir * Ff_norm;

		glm::vec3 torque1 = glm::cross((-centersVector), Ff1);
		glm::vec3 torque2 = glm::cross((centersVector), Ff2);

		obj1.torque += torque1;
		obj2.torque += torque2;

		float alpha1 = glm::length(obj1.torque) / (0.4 * obj1.mass * (0.93) * (0.93));//I = 2/5 * m * r^2
		float alpha2 = glm::length(obj2.torque) / (0.4 * obj2.mass * (0.93) * (0.93));//I = 2/5 * m * r^2

		obj1.angularVel = alpha1;
		obj2.angularVel = alpha2;

		obj1.Move(0.000001);
		obj2.Move(0.000001);
	}
}

GLboolean Game::checkCollision(GameObject& o1, GameObject& o2)
{
	float xDiff = (o1.position.x - o2.position.x) * (o1.position.x - o2.position.x);
	float yDiff = (o1.position.y - o2.position.y) * (o1.position.y - o2.position.y);
	float zDiff = (o1.position.z - o2.position.z) * (o1.position.z - o2.position.z);

	float sumOfDiff = xDiff + yDiff + zDiff;

	if (sqrt(sumOfDiff) <= 1.86) {
		return true;
	}

	return false;
}