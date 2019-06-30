#include "Shader.h"
#include<iostream>
#include <fstream>
#include<sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;  //��std�����ռ�֮��

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;   //����FileBuffer
	ifstream fragmentFile;

	stringstream vertexsstream;
	stringstream fragmentsstream;
	 
	vertexFile.open(vertexPath);  //����  ���ĵ����ܴ򲻿���ʧ��
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(ifstream::failbit || ifstream::badbit); //�ڲ��Ե�ʱ��Ҳ���Կ��ǿ����˵���ԭ�����߼����⻹�ǻ���
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	 

	try     //try ��Tab ���ο����γɽṹ �������Ƿ��
	{
		if (!vertexFile.is_open()||!fragmentFile.is_open())      //û�д򿪾���һ��
		{
			throw exception("open file error");    //����exception�Ͳ���ִ������ֱ���ӵ�catch �
		}
		vertexsstream << vertexFile.rdbuf();     //���һ����û����ִ�еģ���Ϊ����
		fragmentsstream << fragmentFile.rdbuf(); 

		vertexstring = vertexsstream.str();     //ͨ��str()��������� vertexsstreamת����vertexstring
		fragmentstring = fragmentsstream.str();

		vertexsource = vertexstring.c_str();      //ͨ��c_str()���������vertexstringת����vertexsource
		fragmentsource = fragmentstring.c_str();




		unsigned int vertex, fragment;    //�����������޺�����������������GPU�������ҵ�shader���ţ�ID�ţ�
		
		vertex = glCreateShader(GL_VERTEX_SHADER);     //  ���ţ� ���ϵ�glCreateShader,ͷ�ļ���������
		                                                //��Ҫ��һ��vertexshader,���ѷ��Ŵ��vertex�������
		glShaderSource(vertex, 1, &vertexsource,NULL);   //��Դ�������ȥ���������ȸ�shader���ţ��ٸ���λ�������ִ��������ٸ��ַ��������λ�ã��ַ�������ĳ���
		glCompileShader(vertex);                          //���������ɫ������ɶ�����
 		checkCompileError(vertex, "VERTEX");//���һ��   //vertex����ID�����ţ�

		
		


		
		
		fragment = glCreateShader(GL_FRAGMENT_SHADER);        //��һ����ƿ�ӣ���ɫ����
		glShaderSource(fragment, 1, &fragmentsource, NULL); //��ƿ��װ����װ //ƿ�ӣ��ǽ�fragment����ɫ����
															                 //Ҫװ�Ķ�����װ��1���ַ������ַ�����&fragmentsource�����賤��
		glCompileShader(fragment); 
		checkCompileError(fragment, "FRAGMENT");//���һ��

		//�ٰ���������
		ID = glCreateProgram();
		glAttachShader(ID, vertex);     //����ɫ��ճ����ɫ���������档
		glAttachShader(ID, fragment);

		glLinkProgram(ID);                             //����
		checkCompileError(ID, "PROGRAM");//���һ��


		glDeleteShader(vertex);
		glDeleteShader(fragment);



 



	   //����ļ�
		cout << vertexsource << endl;
		cout << fragmentsource << endl;
	}
	catch (const std::exception& ex)  // ��catch)���������������ex
	{
		cout << ex.what();     //�û��ط���
	}





}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::SetUniform3f(const char * paramNameString, glm::vec3 param)   //paramNameString����material.ambient����param���� material->ambient   ��ʾ��a������b����
{
	glUniform3f(glGetUniformLocation( ID, "paramNameString"), param.x, param.y, param.z);

 
}

 
 
void Shader::SetUniform1f(const char * paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, " paramNameString"), param);
}

void Shader::SetUniform1i(const char * paramNameString, float solt)
{
	glUniform1i(glGetUniformLocation(ID, paramNameString), solt);
}

void Shader:: checkCompileError(unsigned int ID, std::string type)
{ 
	int succes;       //����������
	char infoLog[512];     //������512

	if (type != "PROGRAM")     //���VERTEX
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &succes); //Ҫ�������   //��shader   ��Ҫ��Ķ���ķ��ţ�Ҫ��Ķ������ʱ���״̬��������������&succes��
		if (!succes)                              //���ɹ� �Ͱѱ��Ĵ���������ʾ����
		{
			glGetShaderInfoLog(ID,512,NULL,infoLog);        //�����£�ȡ�ı���ʲô����    �����ţ���׼����512��λ�ø��� ���� �㱨�Ķ�������512��Ҫ��Ҫ���ַ�����  ��Ҫ����׼����ʢװ�������ѵ�0��Ԫ�ظ�������� 
			cout.setf(ios::showbase);//��ʾ��������(0x��)
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		}

	}
	else                      //��� PROGRAM
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &succes); 
		if (!succes)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout.setf(ios::showbase);//��ʾ��������(0x��)
			cout << "Program compile error" << infoLog << endl;

		}
	}

}










 