#ifndef GAME_H
#define GAME_H

#include "GameObject.h"
#include "Camera.h"
#include <glm/gtx/perpendicular.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


// Function prototypes
void move_camera(GLfloat deltaTime);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


class Game
{
public:
	Game(GLuint screenWidth, GLuint screenHeight, glm::vec3 camPos);
	~Game();
	void AddGameObject(GameObject& gameobject);
	void AddWall(GameObject& gameobject);
	void Start();

private:
	std::vector<GameObject> ballList;
	std::vector<GameObject> wallList;


	GLFWwindow* window;
	const GLuint screenWidth;
	const GLuint screenHeight;
	

	GLboolean CheckCollision(GameObject& o1, GameObject& o2);
	void PerformCollision(int objNum1, int objNum2);
	void Render();
	void UpdatePositions(GLfloat deltaTime);
};


#endif



