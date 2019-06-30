#include "LightDirection.h"


 LightDirection::LightDirection(glm::vec3 _position,glm::vec3 _angles,glm::vec3 _color)
{
	position = _position;
	angles = _angles;
	color = _color;  
	
	UpdateDirection();  //建构一开始就要呼叫这个方法

}


LightDirection::~LightDirection()
{
}

void LightDirection::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateZ(direction, angles.x);
	direction = glm::rotateZ(direction, angles.y);
	direction = -direction;

}