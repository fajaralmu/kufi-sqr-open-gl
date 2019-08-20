//#include <iostream>
//
//#include "glfw3.h"
//
//void
//error_callback(int error, const char* description)
//{
//	puts(description);
//}
//
//int
//main()
//{
//	glfwSetErrorCallback(error_callback);
//
//	if (!glfwInit())
//	{
//		std::cout << "ERROR: GLFW failed to Initialize" << std::endl;
//		//TODO: Logging
//		return -1;
//	}
//
//	
//	GLFWwindow* Window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
//
//	if (!Window)
//	{
//		glfwTerminate();
//		//TODO: Logging
//		return -1;
//	}
//
//	//TODO: Running loop
//
//	//NOTE: Yay
//	std::cout << "Window Created successfully" << std::endl;
//	glfwTerminate();
//
//	system("pause");
//
//	return 0;
//}