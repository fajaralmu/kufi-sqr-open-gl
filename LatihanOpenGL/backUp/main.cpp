//#include "libs.h"
//
//void
//error_callback(int error, const char* description)
//{
//	puts(description);
//}
//
//int main()
//{
//	glfwSetErrorCallback(error_callback);
//	//INIT GLFW
//	glfwInit();
//	std::cout << "init " << glfwInit() << std::endl;
//	std::cout << "glew_OK " << GLEW_OK << std::endl;
//	//BUAT WINDOW
//	const int LEBAR = 640;
//	const int TINGGI = 480;
//	int frameBufferWidth = 0;
//	int frameBufferHeight = 0;
//
//	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3.2);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3.2);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); MAC os
//
//	GLFWwindow* window = glfwCreateWindow(LEBAR, TINGGI, "Latihan", NULL, NULL);
//	//
//	//glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
//	glViewport(0, 0, frameBufferWidth, frameBufferHeight); //CANVAS
//
//	glfwMakeContextCurrent(window); //PENTING
//
//	//INIT GLEW (Butuh window dan openGL contex
//	glewExperimental = GL_TRUE;
//
//	//Error
//	if (glewInit() != GLEW_OK)
//	{
//		std::cout << "Error main.cpp glew init" << std::endl;
//		glfwTerminate();
//	}
//
//	//LOOP
//	while (!glfwWindowShouldClose(window))
//	{
//		//CHECK UPDATE-----
//
//		//UPDATE-----
//
//		//DRAW-----
//		//Clear
//
//		//Draw
//
//		//End Draw
//	}
//
//	//END
//	glfwTerminate();
//
//	return 0;
//}