#include "Shader.h"
#include<iostream>
#include <fstream>
#include<sstream>
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
		fragmentsouce = fragmentstring.c_str();


		//����ļ�
		cout << vertexsource << endl;
		cout << fragmentsouce << endl;
	}
	catch (const std::exception& ex)  // ��catch)���������������ex
	{
		cout << ex.what();     //�û��ط���
	}





}












//void Shader::

//Shader::~Shader()
//{
//}
