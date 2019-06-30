#pragma once
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Material
{
public:
	Shader* shader;
	unsigned int diffuse;             //glm::vec3输入纯色   unsigned int 是光照纹理
	unsigned int specular;
	glm::vec3  ambient;

	float shininess;


	Material(Shader* _shader, unsigned int _diffuse, unsigned int _specular, glm::vec3  _ambient, float _shininess);   //这里面要配置什么东西进来，你要讲
	~Material();
};

