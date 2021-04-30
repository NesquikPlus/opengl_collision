#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "GameObject.h"
#include "Game.h"
#include "ShaderGroup.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
Game& createGame();

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Game& game = createGame();

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();


        // render objects
        for (int i = 0; i < game.shaderGroups.size(); i++) 
        {
            game.shaderGroups[i].shader->use();
            game.shaderGroups[i].shader->setMat4("projection", projection);
            game.shaderGroups[i].shader->setMat4("view", view);
            game.shaderGroups[i].render();
        }

        //update object positions
        game.updatePositions(deltaTime);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

Game& createGame()
{
    Game* game = new Game();

    Shader* shader = new Shader("resources/shaders/shader.vs", "resources/shaders/shader.fs");
    Model* wallModel = new Model(std::string("resources/objects/wall/wall.obj"));
    Model* earthModel = new Model(std::string("resources/objects/ball/earth.obj"));

    GameObject* w1 = new GameObject(camera, *shader, *wallModel, glm::vec3(0.0f, 0.0f, -4.4f), glm::vec3(0.0f, 0.0f, 0.0f), 1001, glm::vec3(0, 1, 0), 0.0f);
    GameObject* w2 = new GameObject(camera, *shader, *wallModel, glm::vec3(-4.4f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1000, glm::vec3(0, 1, 0), 1.57f);
    GameObject* w3 = new GameObject(camera, *shader, *wallModel, glm::vec3(4.4f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1000, glm::vec3(0, 1, 0), 1.57f);
    GameObject* w4 = new GameObject(camera, *shader, *wallModel, glm::vec3(0.0f, 4.4f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1000, glm::vec3(1, 0, 0), 1.57f);
    GameObject* w5 = new GameObject(camera, *shader, *wallModel, glm::vec3(0.0f, -4.4f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1000, glm::vec3(1, 0, 0), 1.57f);

    GameObject* g1 = new GameObject(camera, *shader, *earthModel, glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(-0.5f, -3.8f, 5.4f), 10);
    GameObject* g2 = new GameObject(camera, *shader, *earthModel, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.7f, 1.0f, -1.0f), 10);
    GameObject* g3 = new GameObject(camera, *shader, *earthModel, glm::vec3(-3.0f, -3.0f, -3.0f), glm::vec3(1.3f, 1.0f, -1.0f), 10);
    GameObject* g4 = new GameObject(camera, *shader, *earthModel, glm::vec3(3.0f, -3.0f, 3.0f), glm::vec3(-1.2f, 0.1f, 1.2f), 10);
    GameObject* g5 = new GameObject(camera, *shader, *earthModel, glm::vec3(-3.0f, 3.0f, -1.0f), glm::vec3(1.5f, -4.2f, 2.2f), 10);

    //TEXTURED OBJECT SHADER GROUP
    ShaderGroup texturedObjects(*shader);
    texturedObjects.addObject(*w1);
    texturedObjects.addObject(*w2);
    texturedObjects.addObject(*w3);
    texturedObjects.addObject(*w4);
    texturedObjects.addObject(*w5);

    texturedObjects.addObject(*g1);
    texturedObjects.addObject(*g2);
    texturedObjects.addObject(*g3);
    texturedObjects.addObject(*g4);
    texturedObjects.addObject(*g5);
    game->addShaderGroup(texturedObjects);


    game->wallList.push_back(w1);
    game->wallList.push_back(w2);
    game->wallList.push_back(w3);
    game->wallList.push_back(w4);
    game->wallList.push_back(w5);

    game->ballList.push_back(g1);
    game->ballList.push_back(g2);
    game->ballList.push_back(g3);
    game->ballList.push_back(g4);
    game->ballList.push_back(g5);


    return *game;
}