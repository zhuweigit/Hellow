#pragma once
#include<string>   //呼叫string这个档
using namespace std;

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	//~Shader();
	 string vertexstring;    //
	 string fragmentstring;
	const char* vertexsource;    //加个const是为了让后面的这个只能写入一次，也就是说写入之后就不能再改变
	const char* fragmentsource;
	unsigned int ID;             //shader program   ID
	void use();
};

