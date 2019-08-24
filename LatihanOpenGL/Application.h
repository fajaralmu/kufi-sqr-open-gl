#pragma once
#include "libs.hpp"
#include "VectorUtil.hpp"
#include "common\ResourceLoader.hpp"
#include "AppObject.h"

using namespace glm;
using namespace std;
using namespace Entity;

namespace App {
	class Application
	{
	public:
		Application();
		~Application();

		// Include standard headers

		GLFWwindow* window;
		GLuint programID;
		GLuint matrixID;

		const string vertexShaderFileName = "vertexShader.txt";
		const string fragmentShaderFileName = "fragmentShader.txt";

		const int WIN_W = 900, WIN_H = 600;

		float horizontalAngle = 3.14f; //toward -Z
		float verticalAngle = 0.0f; //"0" value look at horizon
		float initialFoV = 90.0f; //initial field of view
		float speed = 3.0f; //3 unit/second
		float mouseSpeed = 0.005f;
		float lastTime = glfwGetTime();

		mat4 viewMatrix, projectionMatrix;
		vec3 direction, up, rightMove;

		float velocity = 0.5;
		int counter = 20;
		
		vector<BaseEntity* > objects;

		//lighting
		GLuint lightID, modelMatrixID, viewMatrixID;
		vec3 lightPos= vec3(4, 4, 4);
		int xCount = 3;
		int yCount = 1;
		int zCount = 2;
		int vertexCoordSize = 3;
		int uvCoordSize = 2;
		int normalCoordSize = 3;
		
		std::string textureNames[5] = {
			"a.bmp","b.bmp","c.bmp","d.bmp","e.bmp"
		};
		GLuint textureIDs[5];;
		GLuint mainTexID;
		GLuint worldTexID;
		/*VertexObj mainVertObj;
		VertexObj worldVertObj;*/
		bool handleCollision(BaseEntity* mainObj);
		bool initWindow();
		void initBufferV2();

		void initShader();

		void addObject(BaseEntity * obj);
		void removeObject(BaseEntity * obj);

		double  xpos = 0, ypos = 0;
		bool init = true;
		void handleKeyPress();
		bool initApp();
		int run();
		void getUniformsLocationFromShader();
	};

}