#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/matrix_transform.hpp>
#include "loadShader.hpp"
#include "loadTexture.hpp"
#include "Kontrol.hpp"
#include "loadOBJ.hpp"


using namespace glm;
using namespace std;

int main() {
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
																   // Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global)
	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("vertexShader.txt", "fragmentShader.txt");

	// One color for each vertex. They were generated randomly.
	static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
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

	vector<glm::vec3> vertexarray, normalarray;
	vector<glm::vec2> uvarray;

	bool res = loadOBJ("stall.obj", vertexarray, uvarray, normalarray);

	GLuint vertexbuffer;// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);// Give our vertices to OpenGL.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertexarray.size() * sizeof(glm::vec3), &vertexarray[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, uvarray.size() * sizeof(glm::vec2), &uvarray[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normalarray.size() * sizeof(glm::vec3), &normalarray[0], GL_STATIC_DRAW);

	//GLuint Texture = loadBMP_custom("stall.bmp");
	GLuint Texture = loadDDS("uvmap.dds");
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	cout << "ukuran vert array" << vertexarray.size() << endl;

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	float width = 4, height = 3;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the 	M part)
	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		hitungMatriksDariInput(window);
		mat4 matriksProyeksi = ambilMatriksProyeksi();
		mat4 matriksView = ambilMatriksPandangan();
		mat4 model = mat4(1.0);
		mat4 mvps = matriksProyeksi * matriksView * model;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvps[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
		);

		// 2nd attribute buffer : uvs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		//3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,
			3, //size vec3
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares // Starting from vertex 0; 3 vertices total -> 1 triangle

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);



	return 0;
}