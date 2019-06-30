#include "Cammera.h"




 Cammera::Cammera(glm::vec3 position, float pitch, float yaw,glm::vec3 wordup )
{
	Position = position;
	WordUp = wordup;   //把wordup存起来
	Pitch = pitch;
	Yaw = yaw;
	Forword.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forword.y = glm::sin(Pitch) ;		 
	Forword.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forword, WordUp));   //cross 叉乘！！  灌进来单位向量
 	up = glm::normalize(glm::cross(Right, Forword));
}
//~Cammera();

 void Cammera::updateCameraVectors()   //自定义函数 名字描述了方法，就是更新摄像机的顶点
 {
	 Forword.x = glm::cos(Pitch)*glm::sin(Yaw);
	 Forword.y = glm::sin(Pitch);
	 Forword.z = glm::cos(Pitch)*glm::cos(Yaw);
	 Right = glm::normalize(glm::cross(Forword, WordUp));   //cross 叉乘！！  灌进来单位向量
	 up = glm::normalize(glm::cross(Right, Forword));
 }


//Cammera::~Cammera()
//{
//}
glm::mat4 Cammera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forword, WordUp);
     
}

void Cammera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch += deltaY *SenseX;   //变化太快了 要乘以一个灵敏度
	Yaw  += deltaX* SenseY;
	updateCameraVectors();   //呼叫自己的 updateCameraVertors()'


}
void Cammera:: updateCameraPos()
{
	Position +=Forword*speedZ*0.1f+ Right * speedX*0.1f+  up * speedY*0.1f;  //直接这样glm::vec3(）都是无名向量！！！
}