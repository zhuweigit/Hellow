#include<iostream>
#include"Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


 using namespace std;
 void processInput(GLFWwindow *window);
 //const char* vertexShaderSource;    //代表是字符串源代码？？？？？？？
 //const char* fragmnetShaderSource;    //代表是字符串源代码？？？？？？？

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
	// "uniform vec4 ourColor;  \n"      //只写这个uniform是空的 没写任何数据
	// "void main()\n"
	// "{\n"
	////"   FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
	//// "  FragColor = VertexColor ;\n"    
	// "  FragColor = VertexColor ;\n"
	// "}\n\0";


int main()         //main函数，在这个函数中我们将会实例化GLFW窗口
{




	glfwInit();                                        //初始化GLFW
	//glfwWindowHint函数来配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);     //提示我们使用的opengl主版本号3    我们需要告诉GLFW我们要使用的OpenGL版本是3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);     //提示副版本号3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //提示使用核心模式
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//OPEN GLFW Windows
	//开窗，以后想认这个窗就呼叫这个指针就行了，= 右边是造窗方法（glfwCreateWindow）把信息以参数形式塞进去，以后就用 window来指代开的窗  const塞进就可以以""形式
	GLFWwindow*window = glfwCreateWindow(800, 600, "LearnopenGL", NULL, NULL);
	//没开成功就返回一个-1
	if (window == NULL)
	{
		cout << "没开好窗" << endl;
		glfwTerminate();
		return -1;     //-1代表不正常退出 0才是正常退出
	}
	glfwMakeContextCurrent(window);   //把这个窗口当成当前上下文，也就是用这个窗口了
	
   //调用任何OpenGL的函数之前我们需要初始化GLAD。
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
    glViewport(0, 0, 600, 600);  //开个视口    //调用建立视口函数
	
	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");   //读这两个文件档（文档）
	
																				 
																				 
																				 //需要明文规定告诉opengl要剔除一个面，缺省是两个面都显示
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   //框线模式
	
	// glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); 
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~·
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,1.0f,0,0,  //0
	 0.5f, -0.5f, 0.0f,0,1.0f,0,  //1
	 0.0f,  0.5f, 0,0,0,1.0f,  //2 
	 // 0.5f, -0.5f, 0.0f,         //原来是一个一个输入，实际上太慢，为每个顶点编上编号进行索引
	 // 0.0f,  0.5f, 0.0f,
	 0.8f,0.8f,0.0f,1.0f,0,1.0f,     //3      最后一个不能给  “，”
     -1.0f,1.0f,0.0f,1.f,0,0        //4
	};
	unsigned int indices[] = {     //索引数组  另一种方法
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
	////编译顶点着色器
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建一个着色器对象， 参数是（具体要求描述）创一个什么样的shader
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);    //1个字符串源代码（给出地址）塞进shader
	//glCompileShader(vertexShader);                                 //把shader编译成为二进制

	//	//编译（片段）着色器
	//unsigned int fragmentShader;           //空的片段着色器
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建一个着色器对象， 参数是（具体要求描述）创一个什么样的shader
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);    //1个字符串源代码（给出地址）塞进shader
	//glCompileShader(fragmentShader);                                 //把shader编译成为二进制

	////着色器程序
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();  //glCreateProgram方法造一个程序，并返给我一个程序对象的ID
	//glAttachShader(shaderProgram, vertexShader);    //粘上去
	//glAttachShader(shaderProgram, fragmentShader);  //粘上去
	//glLinkProgram(shaderProgram);                    //链接
	
	// 1. 设置顶点属性指针
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//第0个开始绘制，总共3笔资料，每笔数据形式float,不用变成+-1之间，每笔资料的间隔此处是3个float,第一笔资料的偏移量是多少（此处塞进只有顶点所以0）
//	glEnableVertexAttribArray(0);                  //把第0号资料打开

//	glUseProgram(shaderProgram);
	// 1. 设置顶点属性指针
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);

	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float))); //偏移量要改
	glEnableVertexAttribArray(7);

	// 2. 当我们渲染一个物体时选择要使用着色器程序
	//glUseProgram(shaderProgram);

	
	
	//glDeleteShader(vertexShader);                //着色器对象没用了  删除掉
	//glDeleteShader(fragmentShader);
	
	



	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwSwapBuffers(window);   //交换缓冲区，把图像贴上去
		glfwPollEvents();          //用户按了什么按钮，做了什么捕获消息
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


	    glBindVertexArray(VAO);   //当前画的线
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		//float timeValue = glfwGetTime();   //得到当前的时间存在timeValu里面
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLoation = glGetUniformLocation(shaderProgram, "ourColor");   //get哪个program,其里面的一个叫ourColor的值
 
  //   	glUseProgram(shaderProgram);  //就可以画了   激活着色器程序
		//	
		//glUniform4f(vertexColorLoation, 0.0, greenValue, 0.0f, 1.0f);

		myShader->use();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		  
	    


		glDrawArrays(GL_TRIANGLES, 0, 6);//画成三角形，从0资料起始画，画三组（3个顶点）
		
	}
	glfwTerminate();  //删掉配置的资源
	return 0;

}
 void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
  
 