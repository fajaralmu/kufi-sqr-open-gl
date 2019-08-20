// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include "common\LoadShader.hpp"

using namespace glm;
using namespace std;

GLFWwindow* window;
GLuint vertexArrayID;
GLuint vertexBuffer; //identify vertexBuffer
GLuint programID;

const string vertexShaderFileName = "vertexShader.txt";
const string fragmentShaderFileName = "fragmentShader.txt";

const static GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};



bool initWindow() {
	glfwWindowHint(GLFW_SAMPLES, 4); //4x anti aliasing ->sampling the missing dot on the image
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version of openGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//avoid old openGL


	//open a window and create openGL context
	window = glfwCreateWindow(800, 600, "OPEN GL Fajar", NULL, NULL);
	if (window == NULL) {
		fprintf_s(stderr, "Error creating window");
		glfwTerminate();

		return false;
	}
	cout << ("Window created.. ") << endl;
	glfwMakeContextCurrent(window); //Initialize GLEW
	glewExperimental = true;//Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf_s(stderr, "Failed initialize GLEW");
		return false;
	}
	cout << ("GLEW initialized.. ") << endl;
	return true;

	//
}

void initVertex() {
	
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	//vertexBuffer
	glGenBuffers(1, &vertexBuffer);//generate 1 buffer and the identifier in vertexBuffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//give the vertices to OpenGL
	int size = sizeof(g_vertex_buffer_data);
	cout << "SIZE:" << size << endl;
	glBufferData(GL_ARRAY_BUFFER, size, g_vertex_buffer_data, GL_STATIC_DRAW);

}

void initShader() {
	programID = LoadShaders(vertexShaderFileName.c_str(), fragmentShaderFileName.c_str());
}

void printPressedKeyInfo() {
	bool pressUp = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
	bool pressDown = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
	bool pressRight = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
	bool pressLeft = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;

	std::string pressInfo = "PRESS: ";

	if (pressUp)
		pressInfo += "UP";
	if (pressDown)
		pressInfo += "DOWN";
	if (pressRight)
		pressInfo += "RIGHT";
	if (pressLeft)
		pressInfo += "LEFT";
	if (pressUp || pressDown || pressRight || pressLeft)
		cout << (pressInfo.c_str()) << endl;
}

int main() {

	if (!glfwInit()) {
		fprintf_s(stderr, "Error Initialize GLFW");
		getchar();
		return -1;
	}
	cout << ("GLFW Initialized") << endl;

	bool glewInit = initWindow();
	if (!glewInit) {

		getchar();
		return -1;
	}
	cout << "window init" << endl;
	initVertex();
	cout << "vertex init" << vertexArrayID<<" "<<vertexBuffer<< endl;
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	initShader();
	do {
		printPressedKeyInfo();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0,0,0.4,0);

		//use the shader
		glUseProgram(programID);
	
		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		int size = 3;
		GLenum type = GL_FLOAT;
		GLboolean isNormalized = GL_FALSE;
		GLsizei stride = 0;
		int arrayBufferOffset = 0;

		glVertexAttribPointer(0, size, type, isNormalized, stride, (void *)arrayBufferOffset);
		////=======DRAW=======////
		//triangle
		GLint startingVertex = 0;
		GLsizei totalVertices = 3;
		glDrawArrays(GL_TRIANGLES, startingVertex, totalVertices);
		glDisableVertexAttribArray(0);

		//swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0);
	//	getchar();
	return 0;
}