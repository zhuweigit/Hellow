#version 330 core 
layout (location = 6) in vec3 aPos; 
 layout (location=7) in vec3  aNormal;     //��������ֵ
 layout (location=8) in vec2  aTexCoord ;  

out vec3 FragPos;  //���
out vec3 Normal;    // 
out vec2 TexCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
 

void main() 
{ 
 gl_Position = projMat*viewMat*modelMat*vec4(aPos.xyz, 1.0); 
 FragPos=(modelMat*vec4(aPos.xyz, 1.0)).xyz;   //ת����������ϵ���У��۲������Լ�ͶӰ���󶼲���Ҫת
   Normal= mat3(transpose(inverse(modelMat)))*aNormal;	
   //  Normal= mat3(modelMat)*aNormal;  
	  TexCoord=aTexCoord;
	 
	
}  