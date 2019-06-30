#include "Shader.h"
#include<iostream>
#include <fstream>
#include<sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;  //在std命名空间之下

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;   //建立FileBuffer
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
		fragmentsource = fragmentstring.c_str();




		unsigned int vertex, fragment;    //先宣告两个无号正整数，用来承载GPU返还给我的shader番号（ID号）
		
		vertex = glCreateShader(GL_VERTEX_SHADER);     //  番号！ 不认得glCreateShader,头文件包含宣告
		                                                //我要造一个vertexshader,并把番号存给vertex这个变量
		glShaderSource(vertex, 1, &vertexsource,NULL);   //把源代码读进去，参数：先给shader番号，再给移位进来的字串个数，再给字符串数组的位置，字符串数组的长度
		glCompileShader(vertex);                          //编译这个着色器，变成二进制
 		checkCompileError(vertex, "VERTEX");//检查一下   //vertex就是ID（番号）

		
		


		
		
		fragment = glCreateShader(GL_FRAGMENT_SHADER);        //建一个空瓶子（着色器）
		glShaderSource(fragment, 1, &fragmentsource, NULL); //往瓶里装东西装 //瓶子：是叫fragment的着色器。
															                 //要装的东西：装进1个字符串，字符串在&fragmentsource，无需长度
		glCompileShader(fragment); 
		checkCompileError(fragment, "FRAGMENT");//检查一下

		//再把两个链接
		ID = glCreateProgram();
		glAttachShader(ID, vertex);     //把着色器粘到着色器程序上面。
		glAttachShader(ID, fragment);

		glLinkProgram(ID);                             //链接
		checkCompileError(ID, "PROGRAM");//检查一下


		glDeleteShader(vertex);
		glDeleteShader(fragment);



 



	   //输出文件
		cout << vertexsource << endl;
		cout << fragmentsource << endl;
	}
	catch (const std::exception& ex)  // （catch)收下这个东西命名ex
	{
		cout << ex.what();     //用哗特方法
	}





}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::SetUniform3f(const char * paramNameString, glm::vec3 param)   //paramNameString代替material.ambient，，param代替 material->ambient   表示在a中填入b内容
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
	int succes;       //先声明两个
	char infoLog[512];     //长度是512

	if (type != "PROGRAM")     //检查VERTEX
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &succes); //要查的内容   //查shader   （要查的对象的番号，要查的东西（问编译状态），结果请你存入&succes）
		if (!succes)                              //不成功 就把报的错误问题显示出来
		{
			glGetShaderInfoLog(ID,512,NULL,infoLog);        //做的事：取的报的什么错误    （番号，我准备了512个位置给你 ，你 汇报的东西不是512个要不要把字符给我  不要，我准备的盛装的容器把第0个元素给它结果） 
			cout.setf(ios::showbase);//显示基数符号(0x或)
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		}

	}
	else                      //检查 PROGRAM
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &succes); 
		if (!succes)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout.setf(ios::showbase);//显示基数符号(0x或)
			cout << "Program compile error" << infoLog << endl;

		}
	}

}










 