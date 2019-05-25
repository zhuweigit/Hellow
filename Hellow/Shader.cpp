#include "Shader.h"
#include<iostream>
#include <fstream>
#include<sstream>
using namespace std;  //在std命名空间之下

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;    //建立FileBuffer
	ifstream fragmentFile;

	stringstream vertexsstream;
	stringstream fragmentsstream;
	 
	vertexFile.open(vertexPath);  //开档  打开文档可能打不开会失败
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(ifstream::failbit || ifstream::badbit); //在测试的时候也可以看是开不了档的原因，是逻辑问题还是坏档
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	 

	try     //try 后Tab 两次快速形成结构 来检验是否打开
	{
		if (!vertexFile.is_open()||!fragmentFile.is_open())      //没有打开就扔一个
		{
			throw exception("open file error");    //碰到exception就不会执行下面直接扔到catch 里，
		}
		vertexsstream << vertexFile.rdbuf();     //这个一定是没问题执行的，他为导入
		fragmentsstream << fragmentFile.rdbuf(); 

		vertexstring = vertexsstream.str();     //通过str()这个方法把 vertexsstream转化成vertexstring
		fragmentstring = fragmentsstream.str();

		vertexsource = vertexstring.c_str();      //通过c_str()这个方法把vertexstring转化成vertexsource
		fragmentsouce = fragmentstring.c_str();


		//输出文件
		cout << vertexsource << endl;
		cout << fragmentsouce << endl;
	}
	catch (const std::exception& ex)  // （catch)收下这个东西命名ex
	{
		cout << ex.what();     //用哗特方法
	}





}












//void Shader::

//Shader::~Shader()
//{
//}
