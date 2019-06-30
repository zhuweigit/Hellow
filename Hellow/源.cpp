#include<iostream>
#include"Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include "Cammera.h"
#include "LightDirection.h"
#include "Material.h"
#include "LightPoint.h"
#include "LightSpot.h"


//Load
#define STB_IMAGE_IMPLEMENTATION  //一次就行
#include "stb_image.h"             //哪个文件用都要加上

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


 

using namespace std;
int width, height, nrChannels;

	#pragma region Cammera Declare
	Cammera cammera(glm::vec3(0, 0, 3.0f), glm::radians(-20.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0)); //在世界坐标下摄像机本身的位置和要看的位置此为是原点和世界的UP值
	#pragma endregion

#pragma region  Light Declare							   

	LightSpot light= LightSpot(glm::vec3(0.0f,5.0f,0.0f),glm::vec3(glm::radians(90.0f),0,0),
		glm::vec3(1.0f, 1.0f, 1.0f));       //视频第11::33


#pragma endregion

//全部都是键盘鼠标的操纵
	#pragma region Input Declare
	float lastX;    //鼠标前一次坐标
	float lastY;
	bool firstMouse = true;   //是否是第一次，第一次不知道鼠标的位置  可能会造成变化量很大，所以要进行检测
											 //抬角         右转角
	void processInput(GLFWwindow *window)      //处理事件
	{
		//按 Esc键  窗口关闭
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //轮询按键状态，window就是窗口句柄，key是一个GLFW_KEY_
			glfwSetWindowShouldClose(window, true);

		//看WS键是否按压，若Z按压就进行增减 没有就强制清零
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cammera.speedZ = 0.04f;
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cammera.speedZ = -0.04f;
		else
			cammera.speedZ = 0;

		//看DA键是否按压，若按压X就进行增减 没有强制就清零
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cammera.speedX = 0.04f;
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cammera.speedX = -0.04f;
		else
			cammera.speedX = 0;

		//看EQ键是否按压，若按压Y就进行增减 没有就清零
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			cammera.speedY = 0.04f;
		else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			cammera.speedY = -0.04f;
		else
			cammera.speedY = 0;



	}
	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{ 
		if (firstMouse == true)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
		float deltaX, deltaY;
		deltaX = xpos - lastX;
		deltaY = ypos - lastY;
		cammera.ProcessMouseMovement(deltaX, deltaY);
		lastX = xpos;
		lastY = ypos;    //我要的就是变化量
	   // cout << deltaX << endl;
	}
	 #pragma endregion

	#pragma region Model Data
		//没有用BEO直接用的VAO
		//float vertices[] = {
		//	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标uv 是xy的相对位置-
		//-0.5f, -0.5f, -0.5f,                          0.0f, 0.0f,

		float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};

		//指示10个箱子在世界坐标系的位置  位移向量   定义了是个箱子的位置
		glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		#pragma endregion


	#pragma region Init and Load Textures
		// 加载并生成纹理
		unsigned int  LoadIamgeToGPU(const char* fillename,GLint internalFormat,GLenum format,int textureSlot)  //广义化表示参数，这样才可以多呼叫
		{

			unsigned int  TexBuffer;
			glGenTextures(1,&TexBuffer);     //生成黑框（TexBufferA） 缓冲
			glActiveTexture(GL_TEXTURE0+textureSlot);   //移到0号槽位   
			glBindTexture(GL_TEXTURE_2D, TexBuffer);//绑定到目标


		//	int width, height, nrChannels;	
			unsigned char *data = stbi_load(fillename, &width, &height, &nrChannels, 0);  //把图读进来
			if (data)  //data有内容
			{
				//          朝哪个通道去灌，多级渐远纹理的级别第0等级基本等级，用RGB格式存储	   图不要给边缘     资料形态
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data); //data是单独的数据

				glGenerateMipmap(GL_TEXTURE_2D);    //把绑在目标上的那张图帮他产生Mipmap 
			}
			else
			{
				cout << "load image failed." << endl;
			}
			stbi_image_free(data);   //data释放出来给其他人用
			return  TexBuffer;
		}
		#pragma endregion

int main()         //main函数，在这个函数中我们将会实例化GLFW窗口
{

	# pragma region Open a Window
		glfwInit();                                        //初始化GLFW
		//glfwWindowHint函数来配置GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);     //提示我们使用的opengl主版本号3    我们需要告诉GLFW我们要使用的OpenGL版本是3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);     //提示副版本号3
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //提示使用核心模式
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		//OPEN GLFW Windows
		//开窗，以后想认这个窗就呼叫这个指针就行了，= 右边是造窗方法（glfwCreateWindow）把信息以参数形式塞进去，以后就用 window来指代开的窗  const塞进就可以以""形式
		GLFWwindow*window = glfwCreateWindow(800, 600, "LearnopenGL", NULL, NULL);
		//没开成功就返回一个-1
		if (window == NULL)
		{
			cout << "没开好窗" << endl;
			glfwTerminate();
			return -1;     //-1代表不正常退出 0才是正常退出
		}
		//窗口的开始
		glfwMakeContextCurrent(window);   //把这个窗口当成当前上下文，也就是用这个窗口了  
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  //上下文之后立刻关掉游标
		 //void mouse_callback(GLFWindow* window, double xpos, double ypose)  //error 不完整的类型  调用而已不需要类型
		glfwSetCursorPosCallback(window, mouse_callback);    //回调函数




	  //调用任何OpenGL的函数之前我们需要初始化GLAD。
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
		glViewport(0, 0, 600, 600);  //开个视口    //调用建立视口函数
		stbi_set_flip_vertically_on_load(true);  //坐标轴对应一致
		glEnable(GL_DEPTH_TEST);   //开启Z缓冲
	#pragma endregion
//如果不在mian 函数里建就呼叫不叫它了
	#pragma region Init Shaders
		Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");   //读这两个文件档（文档）
		#pragma endregion 

	#pragma region Init Material
				Material*material = new Material(myShader,
					LoadIamgeToGPU("container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
					LoadIamgeToGPU("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
					glm::vec3(1.0f, 1.0f, 1.0f),
					64.0f);

		#pragma endregion

    #pragma region Init and Load Models to VBO, VAO
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 1. 设置顶点属性指针
		 //            //glVertexAttribPointer或VBO只是建立CPU和GPU之间的逻辑连接，从而实现了CPU数据上传至GPU。但是，数据在GPU端是否可见，即，着色器能否读取到数据，由是否启用了对应的属性决定                            5个在一起，形状就很奇怪 !!!!!!!!!!!!!!!!
		glVertexAttribPointer(6	, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//此是对 //位置资料解析  //第几号栏位，这个位置资料几个分量，步长，偏移量就是起始位置
		glEnableVertexAttribArray(6);     //出于性能考虑，所有顶点着色器的属性（Attribute）变量都是关闭的，glEnableVertexAttribArray的功能，允许顶点着色器读取GPU（服务器端）数据
		                                    //允许顶点着色器读取GPU（服务器端）数据
		//glEnableVertexAttribArray应该在glVertexAttribPointer之前还是之后调用？答案是都可以，只要在绘图调用（glDraw*系列函数）前调用即可。
		glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(3 * sizeof(float))); //纹理坐标资料解析//偏移量要改
		glEnableVertexAttribArray(7);
		glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(6 * sizeof(float))); //纹理坐标资料解析//偏移量要改
		glEnableVertexAttribArray(8);

#pragma endregion 

	#pragma region Init and Load Textures
		//创建缓存，移到0号位绑定
		//unsigned int TexBufferA;
		//TexBufferA =LoadIamgeToGPU("container2.jpg",GL_RGB, GL_RGB,0); 
		unsigned int TexBufferB;
		TexBufferB = LoadIamgeToGPU("container2.png", GL_RGBA, GL_RGBA, 0);
	#pragma endregion 
	
	#pragma region Prepare MVP materices
				glm::mat4 trans;
				glm::mat4 modelMat;
				glm::mat4 viewMat;
				glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		#pragma endregion 

  

	//渲染回圈 一直在渲染
	while (!glfwWindowShouldClose(window))
	{
		//process Input
		processInput(window);
		//清屏擦黑板
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //增补了深度清屏，实现又清颜色又清深度Z缓冲值
		//glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
		glClearColor(0, 0, 0, 0);
 
		//算出旋转矩阵
 		modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(0, 1.0f, 0));       //起始的矩阵，
 
 		viewMat = cammera.GetViewMatrix();
 		//填充：张角45度，宽高比，
    	 projMat = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		//箱满屏实现
 		for (int i = 0; i < 10; i++)
		{
           //set model Material
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);   //位移向量cubePositions[i]
		   //set Model materix projMat here if you want

			//Set Material->Shader Program         
			myShader->use();

			glActiveTexture(GL_TEXTURE0 );   //移到0号槽位   
			glBindTexture(GL_TEXTURE_2D, material->diffuse);//绑定到目标
			glActiveTexture(GL_TEXTURE0 + 1);   //移到0号槽位   
			glBindTexture(GL_TEXTURE_2D, material->specular);//绑定到目标

			//灌进来uniform ！！！！！
  			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			 
			//在这个地方把uniform 值汇进来
			//光照
			 glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f,1.0f,1.0f); 
		 	glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"),0.1f, 0.1f,0.1f);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightPos"),light.position.x, light.position.y, light.position.z);  //与光有关其一   postion 
			glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"),light.color.x,light.color.y,light.color.z);      //与光有关其二   Color
			glUniform3f(glGetUniformLocation(myShader->ID, "lightDirUniform"), light.direction.x, light.direction.y, light.direction.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "CammeraPos"), cammera.Position.x, cammera.Position.y, cammera.Position.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), light.cosPhyInner);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOutter"), light.cosPhyOutter);
			
		/*	衰减值
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP.constant"), light.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP.linear"), light.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP.quadratic"), light.quadratic); */
			

			//光照贴图
			material->shader->SetUniform3f("Material.ambient", material->ambient);
			material->shader->SetUniform1f("Material.diffuse",Shader::DIFFUSE);
			material->shader->SetUniform1f("Material.specular", Shader::SPECULAR);

			material->shader->SetUniform1f("Material.specular", material->specular);
			material->shader->SetUniform1f("Material.shininess", material->shininess);


 
			//Set model
			glBindVertexArray(VAO);   //当前画的线
 			
		    //DrawCall
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		//Clean up ,perpare for next render loop 
		glfwSwapBuffers(window);   //交换缓冲区，把图像贴上去
		glfwPollEvents();          //用户按了什么按钮，做了什么捕获消息
		cammera.updateCameraPos();
	}
	//Exit program
	glfwTerminate();  //删掉配置的资源
	return 0;

}
