#include "ShaderGroup.h"

ShaderGroup::ShaderGroup(Shader& shaderArg)
{
	shader = &shaderArg;
}

void ShaderGroup::addObject(GameObject& obj)
{
	shaderGroupObjects.push_back(&obj);
}

void ShaderGroup::render()
{
	for (int i = 0; i < shaderGroupObjects.size(); i++) {
		shaderGroupObjects[i]->Render();
	}
}


