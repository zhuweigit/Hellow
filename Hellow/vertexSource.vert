#version 330 core 
layout (location = 6) in vec3 aPos; 
 layout (location=7) in vec3  aNormal;     //法向量的值
 layout (location=8) in vec2  aTexCoord ;  

out vec3 FragPos;  //输出
out vec3 Normal;    // 
out vec2 TexCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
 

void main() 
{ 
 gl_Position = projMat*viewMat*modelMat*vec4(aPos.xyz, 1.0); 
 FragPos=(modelMat*vec4(aPos.xyz, 1.0)).xyz;   //转成世界坐标系就行，观察坐标以及投影矩阵都不需要转
   Normal= mat3(transpose(inverse(modelMat)))*aNormal;	
   //  Normal= mat3(modelMat)*aNormal;  
	  TexCoord=aTexCoord;
	 
	
}  