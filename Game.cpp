#include "Game.h"
#include <cmath>
#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

	Game::Game():screenWidth(1600),screenHeight(900)
	{
	    // Init GLFW
	    glfwInit();
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	   	this->window = glfwCreateWindow(screenWidth, screenHeight, "Collisions", nullptr, nullptr);
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
		gameobject.camera = &camera;
		gameObjectsList.push_back(gameobject);
	}

	void Game::Render()
	{
    	while (!glfwWindowShouldClose(window))
    	{
	        glfwPollEvents();

	        GLfloat currentFrame = glfwGetTime();
	        deltaTime = currentFrame - lastFrame;
	        lastFrame = currentFrame;

	        MoveCamera(deltaTime);
	        UpdatePositions(deltaTime);

	        glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	       

			for(int i=0; i < gameObjectsList.size(); i++)
			{
				gameObjectsList[i].Render();
			}

	        // Swap the screen buffers
	        glfwSwapBuffers(this->window);
    	}

	}

	void Game::UpdatePositions(GLfloat deltaTime)
	{
		for(int i=0; i < gameObjectsList.size(); i++)
		{
			gameObjectsList[i].Move(deltaTime);
		}

		for(int i=0; i < gameObjectsList.size(); i++)
		{
			for(int j=i+1; j < gameObjectsList.size(); j++)
			{
				DoCollisions(i,j);
			}
		}
	}



	void Game::DoCollisions(int obj1Num, int obj2Num)
	{
		GameObject& obj1 = gameObjectsList[obj1Num];
		GameObject& obj2 = gameObjectsList[obj2Num];

		if(CheckCollision(obj1, obj2) == true)
		{
			glm::vec3 normal (obj1.position - obj2.position);
			
			//(1,1,tmp) is a point on the plane of interception.
			float tmp = -(normal.x - normal.x * ((obj1.position.x+obj2.position.x)/2) + 
							normal.y - normal.y * ((obj1.position.y+obj2.position.y)/2) - 
							normal.z * ((obj1.position.z+obj2.position.z)/2))/normal.z;
			
			glm::vec3 tangent1(((obj1.position.x+obj2.position.x)/2) - 1, ((obj1.position.y+obj2.position.y)/2) -1, ((obj1.position.z+obj2.position.z)/2) - tmp);
			glm::vec3 tangent2 = glm::cross(tangent1, normal);


			glm::vec3 unitnormal = glm::normalize(normal);
			glm::vec3 unittangent1 = glm::normalize(tangent1);
			glm::vec3 unittangent2 = glm::normalize(tangent2);

			float v1n = glm::dot(obj1.velocity, unitnormal);
			float v2n = glm::dot(obj2.velocity, unitnormal);



			float v1t1_final = glm::dot(obj1.velocity, unittangent1);
			float v1t2_final = glm::dot(obj1.velocity, unittangent2);


			float v2t1_final = glm::dot(obj2.velocity, unittangent1);
			float v2t2_final = glm::dot(obj2.velocity, unittangent2);


			float v1n_final = (v1n * (obj1.mass - obj2.mass) + 2 * (obj2.mass) * v2n) / (obj1.mass+ obj2.mass);
			float v2n_final = (v2n * (obj2.mass - obj1.mass) + 2 * (obj1.mass) * v1n) / (obj1.mass+ obj2.mass);


			
			obj1.velocity = unitnormal * v1n_final + unittangent1 * v1t1_final + unittangent2 * v1t2_final;
			obj2.velocity = unitnormal * v2n_final + unittangent1 * v2t1_final + unittangent2 * v2t2_final;

			obj1.Move(deltaTime);
			obj2.Move(deltaTime);
		}
	}



	GLboolean Game::CheckCollision(GameObject& o1, GameObject& o2)
	{
		float xDiff = (o1.position.x - o2.position.x) * (o1.position.x - o2.position.x);
		float yDiff = (o1.position.y - o2.position.y) * (o1.position.y - o2.position.y); 
		float zDiff = (o1.position.z - o2.position.z) * (o1.position.z - o2.position.z);


		float sumOfDiff = xDiff + yDiff + zDiff;
		float tmp = sqrt(sumOfDiff);


		if(tmp <= 1.86){
			return true;
		}
		
		return false;
	}


	// Moves the camera positions based on user input
	void MoveCamera(GLfloat deltaTime)
	{
	    // Camera controls
	    if(keys[GLFW_KEY_W])
	        camera.ProcessKeyboard(FORWARD, deltaTime);
	    if(keys[GLFW_KEY_S])
	        camera.ProcessKeyboard(BACKWARD, deltaTime);
	    if(keys[GLFW_KEY_A])
	        camera.ProcessKeyboard(LEFT, deltaTime);
	    if(keys[GLFW_KEY_D])
	        camera.ProcessKeyboard(RIGHT, deltaTime);
	}



	// Is called whenever a key is pressed/released via GLFW
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
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

	   	camera.ProcessMouseMovement(xoffset, yoffset);
	}   

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
	    camera.ProcessMouseScroll(yoffset);
	}