#pragma once   //�������һ�����ܣ���������һ�����뵵�������Σ��������������ֹ��������


//�����һ�α���������м�Ķ���  #ifdef CAMERA_H    #endif // DEBUG ,���ң������ǩ�� #define CAMERA_H    �����������˵�һ��if��ʧ�ܾͲ��������������
//#ifdef CAMERA_H   
//#define CAMERA_H   



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
class Cammera
{
public:
//	Cammera(glm::vec3 position,glm::vec3 target,glm::vec3 wordup);   //�������ǹ�����������λ�ã�Ŀ��λ�ã���������
	Cammera(glm::vec3 position, float pitch, float yaw, glm::vec3 wordup );
	//~Cammera();
	glm::vec3 Position;
	glm::vec3 Forword;    //
	glm::vec3 Right;
	glm::vec3  up;
	glm::vec3 WordUp;
	float Pitch;          //д���λ���ܰ�ֵ������������������������� �൱��ȫ�ֱ�������ͨȫ�ֱ���ֻ�ǵ�ǰ�ı��Ӷ��嵽����������Ա�����ǳ�Ա�ӳ�����������ȫ��
	float Yaw;
	 

	float SenseX=0.005f;
	float SenseY=0.005f;
	float speedX = 0;
	float speedY = 0;
	float speedZ = 0;
	void ProcessMouseMovement(float deltaX,float deltaY);//  
	glm::mat4 GetViewMatrix();  //�������
	void updateCameraPos();

private:
	void updateCameraVectors();
};



//#endif // DEBUG


