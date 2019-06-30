#include "Cammera.h"




 Cammera::Cammera(glm::vec3 position, float pitch, float yaw,glm::vec3 wordup )
{
	Position = position;
	WordUp = wordup;   //��wordup������
	Pitch = pitch;
	Yaw = yaw;
	Forword.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forword.y = glm::sin(Pitch) ;		 
	Forword.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forword, WordUp));   //cross ��ˣ���  �������λ����
 	up = glm::normalize(glm::cross(Right, Forword));
}
//~Cammera();

 void Cammera::updateCameraVectors()   //�Զ��庯�� ���������˷��������Ǹ���������Ķ���
 {
	 Forword.x = glm::cos(Pitch)*glm::sin(Yaw);
	 Forword.y = glm::sin(Pitch);
	 Forword.z = glm::cos(Pitch)*glm::cos(Yaw);
	 Right = glm::normalize(glm::cross(Forword, WordUp));   //cross ��ˣ���  �������λ����
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
	Pitch += deltaY *SenseX;   //�仯̫���� Ҫ����һ��������
	Yaw  += deltaX* SenseY;
	updateCameraVectors();   //�����Լ��� updateCameraVertors()'


}
void Cammera:: updateCameraPos()
{
	Position +=Forword*speedZ*0.1f+ Right * speedX*0.1f+  up * speedY*0.1f;  //ֱ������glm::vec3(��������������������
}