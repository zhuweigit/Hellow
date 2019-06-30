#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
class LightSpot
{
public:
	LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color );
	~LightSpot();


	glm::vec3 position;    //灯光所处位置
	glm::vec3 angles;    //旋转角度 
	glm::vec3 direction ;
	glm::vec3 color;      //灯光颜色
	 

	void UpdateDirection();  //呼叫这个方法，就会依照当下的旋转角跟新去更新direction的值

	//float cosPhy = 0.9f;   //手电筒允许的最大照射张角
	//太分明了，显得过渡期生硬就把界限缓化
	float cosPhyInner = 0.9f;
	float cosPhyOutter = 0.85f;
};

