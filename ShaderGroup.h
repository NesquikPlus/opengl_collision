#ifndef SHADERGROUP_H
#define SHADERGROUP_H

#include"GameObject.h"
#include <vector>

class ShaderGroup
{
	public:
		ShaderGroup(Shader& shader);
		void render(void);
		void addObject(GameObject& g1);

		Shader* shader;
		std::vector<GameObject*> shaderGroupObjects;
};

#endif //SHADERGROUP_H