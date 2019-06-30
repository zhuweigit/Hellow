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
#define STB_IMAGE_IMPLEMENTATION  //һ�ξ���
#include "stb_image.h"             //�ĸ��ļ��ö�Ҫ����

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


 

using namespace std;
int width, height, nrChannels;

	#pragma region Cammera Declare
	Cammera cammera(glm::vec3(0, 0, 3.0f), glm::radians(-20.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0)); //����������������������λ�ú�Ҫ����λ�ô�Ϊ��ԭ��������UPֵ
	#pragma endregion

#pragma region  Light Declare							   

	LightSpot light= LightSpot(glm::vec3(0.0f,5.0f,0.0f),glm::vec3(glm::radians(90.0f),0,0),
		glm::vec3(1.0f, 1.0f, 1.0f));       //��Ƶ��11::33


#pragma endregion

//ȫ�����Ǽ������Ĳ���
	#pragma region Input Declare
	float lastX;    //���ǰһ������
	float lastY;
	bool firstMouse = true;   //�Ƿ��ǵ�һ�Σ���һ�β�֪������λ��  ���ܻ���ɱ仯���ܴ�����Ҫ���м��
											 //̧��         ��ת��
	void processInput(GLFWwindow *window)      //�����¼�
	{
		//�� Esc��  ���ڹر�
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //��ѯ����״̬��window���Ǵ��ھ����key��һ��GLFW_KEY_
			glfwSetWindowShouldClose(window, true);

		//��WS���Ƿ�ѹ����Z��ѹ�ͽ������� û�о�ǿ������
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cammera.speedZ = 0.04f;
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cammera.speedZ = -0.04f;
		else
			cammera.speedZ = 0;

		//��DA���Ƿ�ѹ������ѹX�ͽ������� û��ǿ�ƾ�����
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cammera.speedX = 0.04f;
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cammera.speedX = -0.04f;
		else
			cammera.speedX = 0;

		//��EQ���Ƿ�ѹ������ѹY�ͽ������� û�о�����
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
		lastY = ypos;    //��Ҫ�ľ��Ǳ仯��
	   // cout << deltaX << endl;
	}
	 #pragma endregion

	#pragma region Model Data
		//û����BEOֱ���õ�VAO
		//float vertices[] = {
		//	//     ---- λ�� ----       ---- ��ɫ ----     - ��������uv ��xy�����λ��-
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

		//ָʾ10����������������ϵ��λ��  λ������   �������Ǹ����ӵ�λ��
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
		// ���ز���������
		unsigned int  LoadIamgeToGPU(const char* fillename,GLint internalFormat,GLenum format,int textureSlot)  //���廯��ʾ�����������ſ��Զ����
		{

			unsigned int  TexBuffer;
			glGenTextures(1,&TexBuffer);     //���ɺڿ�TexBufferA�� ����
			glActiveTexture(GL_TEXTURE0+textureSlot);   //�Ƶ�0�Ų�λ   
			glBindTexture(GL_TEXTURE_2D, TexBuffer);//�󶨵�Ŀ��


		//	int width, height, nrChannels;	
			unsigned char *data = stbi_load(fillename, &width, &height, &nrChannels, 0);  //��ͼ������
			if (data)  //data������
			{
				//          ���ĸ�ͨ��ȥ�࣬�༶��Զ����ļ����0�ȼ������ȼ�����RGB��ʽ�洢	   ͼ��Ҫ����Ե     ������̬
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data); //data�ǵ���������

				glGenerateMipmap(GL_TEXTURE_2D);    //�Ѱ���Ŀ���ϵ�����ͼ��������Mipmap 
			}
			else
			{
				cout << "load image failed." << endl;
			}
			stbi_image_free(data);   //data�ͷų�������������
			return  TexBuffer;
		}
		#pragma endregion

int main()         //main��������������������ǽ���ʵ����GLFW����
{

	# pragma region Open a Window
		glfwInit();                                        //��ʼ��GLFW
		//glfwWindowHint����������GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);     //��ʾ����ʹ�õ�opengl���汾��3    ������Ҫ����GLFW����Ҫʹ�õ�OpenGL�汾��3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);     //��ʾ���汾��3
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //��ʾʹ�ú���ģʽ
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		//OPEN GLFW Windows
		//�������Ժ�����������ͺ������ָ������ˣ�= �ұ����촰������glfwCreateWindow������Ϣ�Բ�����ʽ����ȥ���Ժ���� window��ָ�����Ĵ�  const�����Ϳ�����""��ʽ
		GLFWwindow*window = glfwCreateWindow(800, 600, "LearnopenGL", NULL, NULL);
		//û���ɹ��ͷ���һ��-1
		if (window == NULL)
		{
			cout << "û���ô�" << endl;
			glfwTerminate();
			return -1;     //-1���������˳� 0���������˳�
		}
		//���ڵĿ�ʼ
		glfwMakeContextCurrent(window);   //��������ڵ��ɵ�ǰ�����ģ�Ҳ���������������  
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  //������֮�����̹ص��α�
		 //void mouse_callback(GLFWindow* window, double xpos, double ypose)  //error ������������  ���ö��Ѳ���Ҫ����
		glfwSetCursorPosCallback(window, mouse_callback);    //�ص�����




	  //�����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD��
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
		glViewport(0, 0, 600, 600);  //�����ӿ�    //���ý����ӿں���
		stbi_set_flip_vertically_on_load(true);  //�������Ӧһ��
		glEnable(GL_DEPTH_TEST);   //����Z����
	#pragma endregion
//�������mian �����ｨ�ͺ��в�������
	#pragma region Init Shaders
		Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");   //���������ļ������ĵ���
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

		// 1. ���ö�������ָ��
		 //            //glVertexAttribPointer��VBOֻ�ǽ���CPU��GPU֮����߼����ӣ��Ӷ�ʵ����CPU�����ϴ���GPU�����ǣ�������GPU���Ƿ�ɼ���������ɫ���ܷ��ȡ�����ݣ����Ƿ������˶�Ӧ�����Ծ���                            5����һ����״�ͺ���� !!!!!!!!!!!!!!!!
		glVertexAttribPointer(6	, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//���Ƕ� //λ�����Ͻ���  //�ڼ�����λ�����λ�����ϼ���������������ƫ����������ʼλ��
		glEnableVertexAttribArray(6);     //�������ܿ��ǣ����ж�����ɫ�������ԣ�Attribute���������ǹرյģ�glEnableVertexAttribArray�Ĺ��ܣ���������ɫ����ȡGPU���������ˣ�����
		                                    //��������ɫ����ȡGPU���������ˣ�����
		//glEnableVertexAttribArrayӦ����glVertexAttribPointer֮ǰ����֮����ã����Ƕ����ԣ�ֻҪ�ڻ�ͼ���ã�glDraw*ϵ�к�����ǰ���ü��ɡ�
		glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(3 * sizeof(float))); //�����������Ͻ���//ƫ����Ҫ��
		glEnableVertexAttribArray(7);
		glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(6 * sizeof(float))); //�����������Ͻ���//ƫ����Ҫ��
		glEnableVertexAttribArray(8);

#pragma endregion 

	#pragma region Init and Load Textures
		//�������棬�Ƶ�0��λ��
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

  

	//��Ⱦ��Ȧ һֱ����Ⱦ
	while (!glfwWindowShouldClose(window))
	{
		//process Input
		processInput(window);
		//�������ڰ�
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //���������������ʵ��������ɫ�������Z����ֵ
		//glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
		glClearColor(0, 0, 0, 0);
 
		//�����ת����
 		modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(0, 1.0f, 0));       //��ʼ�ľ���
 
 		viewMat = cammera.GetViewMatrix();
 		//��䣺�Ž�45�ȣ���߱ȣ�
    	 projMat = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		//������ʵ��
 		for (int i = 0; i < 10; i++)
		{
           //set model Material
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);   //λ������cubePositions[i]
		   //set Model materix projMat here if you want

			//Set Material->Shader Program         
			myShader->use();

			glActiveTexture(GL_TEXTURE0 );   //�Ƶ�0�Ų�λ   
			glBindTexture(GL_TEXTURE_2D, material->diffuse);//�󶨵�Ŀ��
			glActiveTexture(GL_TEXTURE0 + 1);   //�Ƶ�0�Ų�λ   
			glBindTexture(GL_TEXTURE_2D, material->specular);//�󶨵�Ŀ��

			//�����uniform ����������
  			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			 
			//������ط���uniform ֵ�����
			//����
			 glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f,1.0f,1.0f); 
		 	glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"),0.1f, 0.1f,0.1f);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightPos"),light.position.x, light.position.y, light.position.z);  //����й���һ   postion 
			glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"),light.color.x,light.color.y,light.color.z);      //����й����   Color
			glUniform3f(glGetUniformLocation(myShader->ID, "lightDirUniform"), light.direction.x, light.direction.y, light.direction.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "CammeraPos"), cammera.Position.x, cammera.Position.y, cammera.Position.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), light.cosPhyInner);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOutter"), light.cosPhyOutter);
			
		/*	˥��ֵ
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP.constant"), light.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP.linear"), light.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP.quadratic"), light.quadratic); */
			

			//������ͼ
			material->shader->SetUniform3f("Material.ambient", material->ambient);
			material->shader->SetUniform1f("Material.diffuse",Shader::DIFFUSE);
			material->shader->SetUniform1f("Material.specular", Shader::SPECULAR);

			material->shader->SetUniform1f("Material.specular", material->specular);
			material->shader->SetUniform1f("Material.shininess", material->shininess);


 
			//Set model
			glBindVertexArray(VAO);   //��ǰ������
 			
		    //DrawCall
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		//Clean up ,perpare for next render loop 
		glfwSwapBuffers(window);   //��������������ͼ������ȥ
		glfwPollEvents();          //�û�����ʲô��ť������ʲô������Ϣ
		cammera.updateCameraPos();
	}
	//Exit program
	glfwTerminate();  //ɾ�����õ���Դ
	return 0;

}
