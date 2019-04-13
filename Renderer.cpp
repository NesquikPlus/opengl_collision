#include "Renderer.h"
#include <GLFW/glfw3.h>

const GLuint WIDTH = 800, HEIGHT = 600;

Renderer::Renderer(GLfloat* vertices, size_t sizeOfVerticesArray, unsigned int numOfVertices)
{
	this->shader = new Shader("shaders/shader.vs", "shaders/shader.fs");
	this->init(vertices, sizeOfVerticesArray);
    this->numOfVertices = numOfVertices;
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete this->shader;
}


const Shader* Renderer::getShader()
{
    return this->shader;
}


void Renderer::Render(glm::vec3 position)
{
    // Activate shader
    shader->Use();

    // Create transformations
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    model = glm::translate(model, position);
    //model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
    // Get their uniform location
    GLint modelLoc = glGetUniformLocation(shader->Program, "model");
    GLint viewLoc = glGetUniformLocation(shader->Program, "view");
    GLint projLoc = glGetUniformLocation(shader->Program, "projection");
    // Pass them to the shaders
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    // Draw container
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->numOfVertices);
    glBindVertexArray(0);
}


void Renderer::init(GLfloat* vertices, size_t sizeOfVerticesArray)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVerticesArray , vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // Unbind VAO
}    
