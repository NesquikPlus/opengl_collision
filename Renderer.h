#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Renderer
{
public:
	Renderer(GLfloat* vertices, size_t sizeOfVertices, unsigned int numOfVertices);
	~Renderer();

	void Render(glm::vec3 position);
	const Shader* getShader();

private:
	Shader* shader;
	GLuint VAO;
	GLuint VBO;
	void init(GLfloat* vertices, size_t sizeOfVerticesArray);
	unsigned int numOfVertices;
};

#endif
