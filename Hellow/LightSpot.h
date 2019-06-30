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


	glm::vec3 position;    //�ƹ�����λ��
	glm::vec3 angles;    //��ת�Ƕ� 
	glm::vec3 direction ;
	glm::vec3 color;      //�ƹ���ɫ
	 

	void UpdateDirection();  //��������������ͻ����յ��µ���ת�Ǹ���ȥ����direction��ֵ

	//float cosPhy = 0.9f;   //�ֵ�Ͳ�������������Ž�
	//̫�����ˣ��Եù�������Ӳ�Ͱѽ��޻���
	float cosPhyInner = 0.9f;
	float cosPhyOutter = 0.85f;
};

