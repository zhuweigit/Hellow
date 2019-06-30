#pragma once
#include<string>   //呼叫string这个档


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	
	enum Slot    //枚举值
	{
		DIFFUSE,    //0
		SPECULAR     //1
	};
	void use();
	void SetUniform3f(const char*paramNameString,glm::vec3 param);
	void SetUniform1f(const char*paramNameString,float param);
	void SetUniform1i(const char*paramNameString, float solt);   //uniform的名称 槽位

private:
	void checkCompileError(unsigned int ID,std::string type);     //检查函数，参数：   番号，字符串
};

