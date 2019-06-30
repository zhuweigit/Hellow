#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightPoint
{
public:
	LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();
   
	glm::vec3 position;
	glm::vec3 angles;    //旋转角度 
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;

	//衰减值
	float constant;  //常数项衰减值
	float linear;    //一次项衰减值
	float quadratic;  //二次项衰减值
};

