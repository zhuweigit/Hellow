#include "Shader.h"
#include<iostream>
#include <fstream>
#include<sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;  //��std�����ռ�֮��

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;    //����FileBuffer
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


		fragment = glCreateShader(GL_FRAGMENT_SHADER);        //��һ����ƿ�ӣ���ɫ����
		glShaderSource(fragment, 1, &fragmentsource, NULL); //��ƿ��װ����װ //ƿ�ӣ��ǽ�fragment����ɫ����
															                 //Ҫװ�Ķ�����װ��1���ַ������ַ�����&fragmentsource�����賤��
		glCompileShader(fragment); 

		//�ٰ���������
		ID = glCreateProgram();
		glAttachShader(ID, vertex);     //����ɫ��ճ����ɫ���������档
		glAttachShader(ID, fragment);

		glLinkProgram(ID);                             //����

		glDeleteShader(vertex);
		glDeleteShader(fragment);



 



	   //����ļ�
		/*cout << vertexsource << endl;
		cout << fragmentsource << endl;*/
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












//void Shader::

//Shader::~Shader()
//{
//}
