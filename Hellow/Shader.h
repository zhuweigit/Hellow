#pragma once
#include<string>   //����string�����


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
	const char* vertexsource;    //�Ӹ�const��Ϊ���ú�������ֻ��д��һ�Σ�Ҳ����˵д��֮��Ͳ����ٸı�
	const char* fragmentsource;
	unsigned int ID;             //shader program   ID
	
	enum Slot    //ö��ֵ
	{
		DIFFUSE,    //0
		SPECULAR     //1
	};
	void use();
	void SetUniform3f(const char*paramNameString,glm::vec3 param);
	void SetUniform1f(const char*paramNameString,float param);
	void SetUniform1i(const char*paramNameString, float solt);   //uniform������ ��λ

private:
	void checkCompileError(unsigned int ID,std::string type);     //��麯����������   ���ţ��ַ���
};

