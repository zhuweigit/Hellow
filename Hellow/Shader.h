#pragma once
#include<string>   //����string�����
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
	void use();
};

