#pragma once   //与下面的一样功能！！！最怕一个编译档编译两次，所以这个就能阻止编译两次


//如果第一次编译就运行中间的东西  #ifdef CAMERA_H    #endif // DEBUG ,并且（定义标签） #define CAMERA_H    若编译编译过了第一行if都失败就不会编译下面的语句
//#ifdef CAMERA_H   
//#define CAMERA_H   



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
class Cammera
{
public:
//	Cammera(glm::vec3 position,glm::vec3 target,glm::vec3 wordup);   //参数就是灌进来：摄像机位置，目标位置，世界坐标
	Cammera(glm::vec3 position, float pitch, float yaw, glm::vec3 wordup );
	//~Cammera();
	glm::vec3 Position;
	glm::vec3 Forword;    //
	glm::vec3 Right;
	glm::vec3  up;
	glm::vec3 WordUp;
	float Pitch;          //写这个位置能把值存进来！！！！！！！！！！ 相当于全局变量，普通全局变量只是当前文本从定义到结束，而成员变量是成员从出生到死亡的全局
	float Yaw;
	 

	float SenseX=0.005f;
	float SenseY=0.005f;
	float speedX = 0;
	float speedY = 0;
	float speedZ = 0;
	void ProcessMouseMovement(float deltaX,float deltaY);//  
	glm::mat4 GetViewMatrix();  //这个方法
	void updateCameraPos();

private:
	void updateCameraVectors();
};



//#endif // DEBUG


