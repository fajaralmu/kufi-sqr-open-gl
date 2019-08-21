// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <random>
#include <string.h>
// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include "common\ResourceLoader.hpp"

using namespace glm;
using namespace std;

GLFWwindow* window;
GLuint vertexArrayID;
GLuint textureID;
GLuint vertexBuffer; //identify vertexBuffer
GLuint colorBuffer;
GLuint programID;
GLuint matrixID;

const string vertexShaderFileName = "vertexShader.txt";
const string fragmentShaderFileName = "fragmentShader.txt";

const int WIN_W = 900, WIN_H = 600;
const static GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};
static GLfloat g_color_buffer_data[] = {
	0.583f, 0.771f, 0.014f,
	0.609f, 0.115f, 0.436f,
	0.327f, 0.483f, 0.844f,
	0.822f, 0.569f, 0.201f,
	0.435f, 0.602f, 0.223f,
	0.310f, 0.747f, 0.185f,
	0.597f, 0.770f, 0.761f,
	0.559f, 0.436f, 0.730f,
	0.359f, 0.583f, 0.152f,
	0.483f, 0.596f, 0.789f,
	0.559f, 0.861f, 0.639f,
	0.195f, 0.548f, 0.859f,
	0.014f, 0.184f, 0.576f,
	0.771f, 0.328f, 0.970f,
	0.406f, 0.615f, 0.116f,
	0.676f, 0.977f, 0.133f,
	0.971f, 0.572f, 0.833f,
	0.140f, 0.616f, 0.489f,
	0.997f, 0.513f, 0.064f,
	0.945f, 0.719f, 0.592f,
	0.543f, 0.021f, 0.978f,
	0.279f, 0.317f, 0.505f,
	0.167f, 0.620f, 0.077f,
	0.347f, 0.857f, 0.137f,
	0.055f, 0.953f, 0.042f,
	0.714f, 0.505f, 0.345f,
	0.783f, 0.290f, 0.734f,
	0.722f, 0.645f, 0.174f,
	0.302f, 0.455f, 0.848f,
	0.225f, 0.587f, 0.040f,
	0.517f, 0.713f, 0.338f,
	0.053f, 0.959f, 0.120f,
	0.393f, 0.621f, 0.362f,
	0.673f, 0.211f, 0.457f,
	0.820f, 0.883f, 0.371f,
	0.982f, 0.099f, 0.879f
};
static const GLfloat g_uv_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};
//position
//vec3 cameraPositionDefault = vec3(4, 3, 3); //in world space
//vec3 cameraLookAtPositionDefault = vec3(0, 0, 0); //look at position
//vec3 headPositionDefault = vec3(0, 1, 0);// 0,-1,0 to look upside down

vec3 position = vec3(0, 0, 5);
float horizontalAngle = 3.14f; //toward -Z
float verticalAngle = 0.0f; //"0" value look at horizon
float initialFoV = 45.0f; //initial field of view
float speed = 3.0f; //3 unit/second
float mouseSpeed = 0.005f;
float lastTime = glfwGetTime();
//
//vec3 cameraPosition = vec3(4, 3, 3); //in world space
//vec3 cameraLookAtPosition = vec3(0, 0, 0); //look at position
//vec3 headPosition = vec3(0, 1, 0);// 0,-1,0 to look upside down

mat4 viewMatrix, projectionMatrix;
vec3 direction, up, rightMove;

float velocity = 0.5;
int counter = 20;


void printVector(vec3 vec, string name) {
	std::cout << name << ", x:" << vec.x << " y:" << vec.y << " z:" << vec.z << endl;
}

void setPosToDefault() {
	/*cameraPosition = cameraPositionDefault;
	cameraLookAtPosition = cameraLookAtPositionDefault;
	headPosition = headPositionDefault;*/

	glfwSetCursorPos(window, WIN_W / 2, WIN_H / 2);
}

bool initWindow() {
	glfwWindowHint(GLFW_SAMPLES, 4); //4x anti aliasing ->sampling the missing dot on the image
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version of openGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//avoid old openGL


	//open a window and create openGL context
	window = glfwCreateWindow(WIN_W, WIN_H, "OPEN GL Fajar", NULL, NULL);
	if (window == NULL) {
		fprintf_s(stderr, "Error creating window");
		glfwTerminate();

		return false;
	}
	std::cout << ("Window created.. ") << endl;
	glfwMakeContextCurrent(window); //Initialize GLEW
	glewExperimental = true;//Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf_s(stderr, "Failed initialize GLEW");
		return false;
	}
	std::cout << ("GLEW initialized.. ") << endl;
	return true;

	//
}

void initBuffer() {

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	/*VERTEX BUFFER*/
	glGenBuffers(1, &vertexBuffer);//generate 1 buffer and the identifier in vertexBuffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//give the vertices to OpenGL
	int size = sizeof(g_vertex_buffer_data);
	//std::cout << "SIZE:" << size << endl;
	glBufferData(GL_ARRAY_BUFFER, size, g_vertex_buffer_data, GL_STATIC_DRAW);

	/*COLOR BUFFER*/ // NOW USE TEXTURE
	/*
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	*/
	/*TEXTURE BUFFER*/
//	textureID = loadBMP_custom("number.bmp");
	textureID = loadDDS("uvmap.dds");

	glGenBuffers(1, &textureID);
	glBindBuffer(GL_ARRAY_BUFFER, textureID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

}

void initShader() {
	programID = LoadShaders(vertexShaderFileName.c_str(), fragmentShaderFileName.c_str());
}

void handleKeyPress() {
	double currentTime = glfwGetTime();

	float deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;
	//printVector(position, "position");

	bool pressUp = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
	bool pressDown = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
	bool pressRight = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
	bool pressLeft = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
	bool pressO = glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;

	double  xpos = 0, ypos = 0;
	glfwGetCursorPos(window, &xpos, &ypos);

	//reset ke tengah
	glfwSetCursorPos(window, WIN_W / 2, WIN_H / 2);

	//compute orientation
	horizontalAngle += mouseSpeed * deltaTime * float(WIN_W / 2 - xpos);
	//std::cout << "horizontal angle: " << horizontalAngle << endl;
	verticalAngle += mouseSpeed * deltaTime * float(WIN_H / 2 - ypos);
	//std::cout << xpos << "," << ypos << endl;
	direction = vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	rightMove = vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);
	up = glm::cross(rightMove, direction);

	//forward
	if (pressUp) {
		position += direction * deltaTime *speed;
	}
	//backward
	if (pressDown) {
		position -= direction * deltaTime *speed;
	}
	//right
	if (pressRight) {
		position += rightMove * deltaTime *speed;
		printVector(rightMove, "rightMove");
	}
	//left
	if (pressLeft) {
		position -= rightMove * deltaTime *speed;
		printVector(rightMove, "rightMove");
	}


	//if (pressUp || pressO || pressDown || pressRight || pressLeft) {
	//	std::cout << "control press" << endl;
	//	printVector(rightMove, "right move");


}


int main() {

	if (!glfwInit()) {
		fprintf_s(stderr, "Error Initialize GLFW");
		getchar();
		return -1;
	}
	std::cout << ("GLFW Initialized") << endl;

	bool glewInit = initWindow();
	if (!glewInit) {

		getchar();
		return -1;
	}
	std::cout << "window init" << endl;
	initBuffer();

	std::cout << "vertex init" << vertexArrayID << " " << vertexBuffer << endl;
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	/*use the shader*/
	initShader();
	glUseProgram(programID);

	matrixID = glGetUniformLocation(programID, "MVP");
	std::cout << "matrixID: " << matrixID << ", programID: " << programID << endl;
	//reset ke tengah
	glfwSetCursorPos(window, WIN_W / 2, WIN_H / 2);

	do {
		glEnable(GL_DEPTH_TEST); // z component
		glDepthFunc(GL_LESS); //accept fragment if it closer to the camera than the former one
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0.4, 0);

		handleKeyPress();

		/*COMPUTE COORDS*/
		//projection
		float angle = 45.0;
		float aspectRatio = (float)WIN_W / (float)WIN_H;
		float nearClippingPane = 0.1f;
		float farClippingPane = 100.0f; //display range: 0.1 - 100.0f


		//model at origin
		mat4 model = glm::mat4(1.0f);
		//ViewModelProjection : mult of 3 matrices
		mat4 projection = glm::perspective(glm::radians(angle), aspectRatio, nearClippingPane, farClippingPane);

		//camera matrix
		mat4 view = glm::lookAt(position, position + direction, up);

		//std::cout << position.x << "-" << position.y << "-" << position.z << "-" << direction.b << "-" << direction.g << endl;
		mat4 mvp = projection * view * model;

		//send to currently bound shader
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);


		/*1ST ATTRIBUTE BUFFER : VERTICES*/
		int size = 3;
		GLenum type = GL_FLOAT;
		GLboolean isNormalized = GL_FALSE;
		GLsizei stride = 0;
		int arrayBufferOffset = 0;


		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, size, type, isNormalized, stride, (void *)arrayBufferOffset);

		/*2ND ATRIBUTE BUFFER: latest=> UV, former=> COLOR*/
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, textureID);
		int coordSize = 2;
		glVertexAttribPointer(1, coordSize, type, isNormalized, stride, (void *)arrayBufferOffset);

		/*DRAW*/
		//triangle
		GLint startingVertex = 0;
		GLsizei totalVertices = sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]);
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