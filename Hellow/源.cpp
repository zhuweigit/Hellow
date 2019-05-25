#include<iostream>
#include"Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


 using namespace std;
 void processInput(GLFWwindow *window);
 //const char* vertexShaderSource;    //�������ַ���Դ���룿������������
 //const char* fragmnetShaderSource;    //�������ַ���Դ���룿������������

 //const char *vertexShaderSource = "#version 330 core\n"
	// "layout (location = 6) in vec3 aPos;\n"
	// "layout (location = 7) in vec3 aColor;\n"
	// "out vec4 VertexColor;\n"
	// 
	//// "out vec4 VertexColor;    \n"
	////  "out vec4 VertexColor;\n"
	// "void main()\n"
	// "{\n" 
	// "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
 //	 // "  VertexColor = vec4(0 ,0 , 0, 1.0);\n" 
	// "  VertexColor = vec4(aColor.x,aColor.y,aColor.z,10f);\n"
	// "}\0";
 //const char *fragmentShaderSource = "#version 330 core\n"
 //  "out vec4 FragColor;\n"
	//"in vec4 VertexColor;      \n" 
	// //"int vec4 vertexColor;\n"
	// "uniform vec4 ourColor;  \n"      //ֻд���uniform�ǿյ� ûд�κ�����
	// "void main()\n"
	// "{\n"
	////"   FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
	//// "  FragColor = VertexColor ;\n"    
	// "  FragColor = VertexColor ;\n"
	// "}\n\0";


int main()         //main��������������������ǽ���ʵ����GLFW����
{




	glfwInit();                                        //��ʼ��GLFW
	//glfwWindowHint����������GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);     //��ʾ����ʹ�õ�opengl���汾��3    ������Ҫ����GLFW����Ҫʹ�õ�OpenGL�汾��3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);     //��ʾ���汾��3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //��ʾʹ�ú���ģʽ
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//OPEN GLFW Windows
	//�������Ժ�����������ͺ������ָ������ˣ�= �ұ����촰������glfwCreateWindow������Ϣ�Բ�����ʽ����ȥ���Ժ���� window��ָ�����Ĵ�  const�����Ϳ�����""��ʽ
	GLFWwindow*window = glfwCreateWindow(800, 600, "LearnopenGL", NULL, NULL);
	//û���ɹ��ͷ���һ��-1
	if (window == NULL)
	{
		cout << "û���ô�" << endl;
		glfwTerminate();
		return -1;     //-1���������˳� 0���������˳�
	}
	glfwMakeContextCurrent(window);   //��������ڵ��ɵ�ǰ�����ģ�Ҳ���������������
	
   //�����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
    glViewport(0, 0, 600, 600);  //�����ӿ�    //���ý����ӿں���
	
	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");   //���������ļ������ĵ���
	
																				 
																				 
																				 //��Ҫ���Ĺ涨����openglҪ�޳�һ���棬ȱʡ�������涼��ʾ
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   //����ģʽ
	
	// glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); 
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~��
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,1.0f,0,0,  //0
	 0.5f, -0.5f, 0.0f,0,1.0f,0,  //1
	 0.0f,  0.5f, 0,0,0,1.0f,  //2 
	 // 0.5f, -0.5f, 0.0f,         //ԭ����һ��һ�����룬ʵ����̫����Ϊÿ��������ϱ�Ž�������
	 // 0.0f,  0.5f, 0.0f,
	 0.8f,0.8f,0.0f,1.0f,0,1.0f,     //3      ���һ�����ܸ�  ������
     -1.0f,1.0f,0.0f,1.f,0,0        //4
	};
	unsigned int indices[] = {     //��������  ��һ�ַ���
	0,1,2,
	2,3,1,
	2,4,0


	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	  
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	////���붥����ɫ��
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);//����һ����ɫ������ �����ǣ�����Ҫ����������һ��ʲô����shader
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);    //1���ַ���Դ���루������ַ������shader
	//glCompileShader(vertexShader);                                 //��shader�����Ϊ������

	//	//���루Ƭ�Σ���ɫ��
	//unsigned int fragmentShader;           //�յ�Ƭ����ɫ��
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//����һ����ɫ������ �����ǣ�����Ҫ����������һ��ʲô����shader
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);    //1���ַ���Դ���루������ַ������shader
	//glCompileShader(fragmentShader);                                 //��shader�����Ϊ������

	////��ɫ������
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();  //glCreateProgram������һ�����򣬲�������һ����������ID
	//glAttachShader(shaderProgram, vertexShader);    //ճ��ȥ
	//glAttachShader(shaderProgram, fragmentShader);  //ճ��ȥ
	//glLinkProgram(shaderProgram);                    //����
	
	// 1. ���ö�������ָ��
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//��0����ʼ���ƣ��ܹ�3�����ϣ�ÿ��������ʽfloat,���ñ��+-1֮�䣬ÿ�����ϵļ���˴���3��float,��һ�����ϵ�ƫ�����Ƕ��٣��˴�����ֻ�ж�������0��
//	glEnableVertexAttribArray(0);                  //�ѵ�0�����ϴ�

//	glUseProgram(shaderProgram);
	// 1. ���ö�������ָ��
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);

	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float))); //ƫ����Ҫ��
	glEnableVertexAttribArray(7);

	// 2. ��������Ⱦһ������ʱѡ��Ҫʹ����ɫ������
	//glUseProgram(shaderProgram);

	
	
	//glDeleteShader(vertexShader);                //��ɫ������û����  ɾ����
	//glDeleteShader(fragmentShader);
	
	



	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwSwapBuffers(window);   //��������������ͼ������ȥ
		glfwPollEvents();          //�û�����ʲô��ť������ʲô������Ϣ
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


	    glBindVertexArray(VAO);   //��ǰ������
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		//float timeValue = glfwGetTime();   //�õ���ǰ��ʱ�����timeValu����
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLoation = glGetUniformLocation(shaderProgram, "ourColor");   //get�ĸ�program,�������һ����ourColor��ֵ
 
  //   	glUseProgram(shaderProgram);  //�Ϳ��Ի���   ������ɫ������
		//	
		//glUniform4f(vertexColorLoation, 0.0, greenValue, 0.0f, 1.0f);

		myShader->use();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		  
	    


		glDrawArrays(GL_TRIANGLES, 0, 6);//���������Σ���0������ʼ���������飨3�����㣩
		
	}
	glfwTerminate();  //ɾ�����õ���Դ
	return 0;

}
 void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
  
 