#include "Game.h"
#include <cmath>
#include <iostream>
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/projection.hpp>

bool paused = false;
Camera* camera;
bool keys[1024];
GLfloat lastX, lastY;
bool firstMouse = true;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

Game::Game(GLuint screenWidth, GLuint screenHeight, glm::vec3 camPos):screenWidth(screenWidth),screenHeight(screenHeight)
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

   	window = glfwCreateWindow(screenWidth, screenHeight, "Collision3D", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    camera = new Camera(camPos);
    lastX = screenWidth/2;
    lastY = screenHeight/2;

	glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

Game::~Game()
{
	glfwTerminate();
}


void Game::Start()
{
	this->Render();
}


void Game::AddGameObject(GameObject& gameobject)
{	
	gameobject.camera = camera;
	ballList.push_back(gameobject);
}

void Game::AddWall(GameObject& gameobject)
{
	gameobject.camera = camera;
	wallList.push_back(gameobject);
}


void Game::Render()
{
	while (!glfwWindowShouldClose(window))
	{
        glfwPollEvents();

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        move_camera(deltaTime);
        UpdatePositions(deltaTime);

        glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       

		for(int i=0; i < ballList.size(); i++){
			ballList[i].Render();
		}

   		for(int i=0; i < wallList.size(); i++){
			wallList[i].Render();
		}

        glfwSwapBuffers(this->window);
	}

}

void Game::UpdatePositions(GLfloat deltaTime)
{
	if(paused)
		return;

	for(int i=0; i < ballList.size(); i++)
	{

		if(ballList[i].position.x > 3.5f && ballList[i].velocity.x > 0)
			ballList[i].velocity.x *= -1;
		else if(ballList[i].position.x < -3.5f && ballList[i].velocity.x < 0)
			ballList[i].velocity.x *= -1;

		if(ballList[i].position.y > 3.5f && ballList[i].velocity.y > 0)
			ballList[i].velocity.y *= -1;
		else if(ballList[i].position.y < -3.5f && ballList[i].velocity.y < 0)
			ballList[i].velocity.y *= -1;

		if(ballList[i].position.z > 3.5f && ballList[i].velocity.z > 0)
			ballList[i].velocity.z *= -1;
		else if(ballList[i].position.z < -3.5f && ballList[i].velocity.z < 0)
			ballList[i].velocity.z *= -1;


		ballList[i].Move(deltaTime);
	}

	for(int i=0; i < ballList.size(); i++)
	{
		for(int j=i+1; j < ballList.size(); j++)
		{
			PerformCollision(i,j);
		}
	}
}


void Game::PerformCollision(int obj1Num, int obj2Num)
{
	GameObject& obj1 = ballList[obj1Num];
	GameObject& obj2 = ballList[obj2Num];

	if(CheckCollision(obj1, obj2) == true)
	{
		glm::vec3 centersVector = (obj1.position - obj2.position);
		centersVector = glm::normalize(centersVector);

		glm::vec3 v1proj = glm::proj(obj1.velocity, centersVector);
		glm::vec3 v2proj = glm::proj(obj2.velocity, centersVector);

		float v1n =  -1.0f * glm::length(v1proj);
		float v2n =  glm::length(v2proj);

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

		float alpha1 = glm::length(obj1.torque) / (0.4 * obj1.mass * (0.93)*(0.93));//I = 2/5 * m * r^2
		float alpha2 = glm::length(obj2.torque) / (0.4 * obj2.mass * (0.93)*(0.93));//I = 2/5 * m * r^2

		obj1.angularVel = alpha1;
		obj2.angularVel = alpha2;

		obj1.Move(0.000001);
		obj2.Move(0.000001);
	}
}

GLboolean Game::CheckCollision(GameObject& o1, GameObject& o2)
{
	float xDiff = (o1.position.x - o2.position.x) * (o1.position.x - o2.position.x);
	float yDiff = (o1.position.y - o2.position.y) * (o1.position.y - o2.position.y); 
	float zDiff = (o1.position.z - o2.position.z) * (o1.position.z - o2.position.z);

	float sumOfDiff = xDiff + yDiff + zDiff;

	if(sqrt(sumOfDiff) <= 1.86){
		return true;
	}
	
	return false;
}


// Moves the camera positions based on user input
void move_camera(GLfloat deltaTime)
{
    // Camera controls
    if(keys[GLFW_KEY_W])
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera->ProcessKeyboard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera->ProcessKeyboard(RIGHT, deltaTime);
}



// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		if(paused == true)
			paused = false;
		else
			paused = true;
	}

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;  
}



void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos; 
    
    lastX = xpos;
    lastY = ypos;

   	camera->ProcessMouseMovement(xoffset, yoffset);
}   

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}
