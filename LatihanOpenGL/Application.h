#pragma once

#include "libs.hpp"
#include "VectorUtil.hpp"
#include "common\ResourceLoader.hpp"
#include "AppObject.h"
#include "GL/freeglut.h"
#include "GL/glut.h"
#include <map>
#include <iomanip>
#include <sstream>


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
		void mouseProcess(BaseEntity * obj, int b, int s, double mouse_x, double mouse_y);
		const int WIN_W = 800, WIN_H = 600;
		const GLint view_port[4] = {
			0,0,WIN_W,WIN_H
		};

		float horizontalAngleBase = 3.14f; //toward -Z
		float horizontalAngle = 3.14f; //toward -Z
		float verticalAngleBase = 0.0f;
		float verticalAngle = 0.0f; //"0" value look at horizon
		float initialFoV = 90.0f; //initial field of view
		float speed = 3.0f; //3 unit/second
		float mouseSpeed = 0.005f;
		float lastTime = glfwGetTime();
		bool pointerMode = false;
		int cubeDimension = 0;
		int layoutType = 1;

		GLdouble mouseX, mouseY;
		GLdouble mouseActualX = 0, mouseActualY = 0;

		mat4 viewMatrix, projectionMatrix;
		vec3 direction, up, rightMove;

		float velocity = 0.5;
		int counter = 20;
		vec3 vertexPos(mat4 mvp, vec3 input, bool ismain);
		vector<BaseEntity* > objects;
		vector<BaseEntity*> activeObj;
		map<char, GLuint> textTextureIDs;
		const int staticObjCount = 24;
		//lighting
		GLuint lightID, modelMatrixID, viewMatrixID;
		vec3 lightPos = vec3(4, 4, 4);
		/*int xCount = 25;
		int yCount = 13;
		int zCount = 1;*/
		int vertexCoordSize = 3;
		int uvCoordSize = 2;
		int normalCoordSize = 3;

		std::string textureNames[5] = {
			"a.bmp","b.bmp","c.bmp","d.bmp","e.bmp"
		};

		std::string textureForTextNames[39] = {
			"a","b","c","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","1","2","3","4","5","6","7","8","9","0","_","-",".","+",
		};
		
		GLuint textureIDs[5];;
		GLuint normalIDs[5];
		GLuint mainTexID;
		GLuint worldTexID;
		vec3 movement;
		/*VertexObj mainVertObj;
		VertexObj worldVertObj;*/
		bool handleCollision(BaseEntity* mainObj, mat4 mvp);
		void createObject(int xCount, int yCount, int zCount, vec3 BaseDimension, vec3 basePosition, double padding);
		void printText(string text);
		bool initWindow();
		void initBufferV2();
		GLdouble* mat4ToDoubleArray(mat4 mat);

		void initShader();

		void addObject(BaseEntity * obj);
		void removeAnObject(BaseEntity * obj);
		void getAllActiveObj();

		double  xpos = 0, ypos = 0;
		bool init = true;
		void handleMotionKeyPress();
		bool initApp();
		int run();
		void getUniformsLocationFromShader();
		vec3 getMouseMovement(bool sleep = true);
	};

}

//==========================BACK UP COLLISION ===========================
/*printVector(winCoord, "===OBJ POS GLUPROJ CENTER");
printVector(winCoordLT, "===OBJ POS GLUPROJ LT");
printVector(winCoordLB, "===OBJ POS GLUPROJ LB");
printVector(winCoordRT, "===OBJ POS GLUPROJ RT");
printVector(winCoordRB, "===OBJ POS GLUPROJ RB");
printVector(obj->position, "===OBJ POSS");
printVector(vec3(xAppWin, yAppWin, 0), "===MOUSE_POS_CALCULATED");
cout << "cos = " << cosValue << " distance= " << distance << endl;
printVector(vec3(horizontalAngle, verticalAngle, 0), "H & V ANGLE");
cout << "IN POSITION : " << inPosition << endl;*/

//mouse
//vec3 position = obj->position + direction;
//double deltaAngle = horizontalAngleBase - horizontalAngle;
//double tanValue = tan(deltaAngle);
//double sinValue = sin(deltaAngle);
//double cosValue = cos(deltaAngle);
//double baseDistance = (cosValue * position.x);
//double deltaDistance = (sinValue * position.z);
//double distance = (position.x) - baseDistance + (deltaDistance > baseDistance ? 0 : deltaDistance);
////	position.z += cosValue *  position.z;
//position.x += (distance);// +deltaDistance;
//double x, y;
//double xTemp, yTemp;
//glfwGetCursorPos(window, &x, &y);
//xTemp = x; yTemp = y;
////obj coord on viewport
//GLdouble model_view[16];
//glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
//
//GLdouble projection_mat[16];
////	glGetDoublev(GL_PROJECTION_MATRIX, projection_mat);
//GLint viewPort[4];
//glGetIntegerv(GL_VIEWPORT, viewPort);
//mat4 mv = obj->view * obj->model;
//mat4 proj = obj->projection;
////GLdouble model_view[16], projection_mat[16];// = mat4ToDoubleArray(obj->projection);
//int xi = 0;
//int yi = 0;
//xi = 0; yi = 0;
//for (int i = 0; i < 16; i++) {
//	projection_mat[i] = proj[xi][yi];
//	yi++;
//	if (yi >= 4) {
//		yi = 0;
//		xi++;
//	}
//}

//GLint viewPort[4] = { 0,0,800,600 };
//
//float windowCoordinate[3];
////
//float windowCoordinateLT[3];
//float windowCoordinateLB[3];
//float windowCoordinateRT[3];
//float windowCoordinateRB[3];
//
//int res = glhProjectf(position.x, position.y, position.z,
//	model_view, projection_mat, viewPort, windowCoordinate);
////
//float halfDimensionX = obj->dimension.x / 2;
//float halfDimensionY = obj->dimension.y / 2;
//
//int resRB = glhProjectf(position.x - halfDimensionX, position.y + halfDimensionY, position.z,
//	model_view, projection_mat, viewPort, windowCoordinateRB);
//int resRT = glhProjectf(position.x - halfDimensionX, position.y - halfDimensionY, position.z,
//	model_view, projection_mat, viewPort, windowCoordinateRT);
//int resLB = glhProjectf(position.x + halfDimensionX, position.y + halfDimensionY, position.z,
//	model_view, projection_mat, viewPort, windowCoordinateLB);
//int resLT = glhProjectf(position.x + halfDimensionX, position.y - halfDimensionY, position.z,
//	model_view, projection_mat, viewPort, windowCoordinateLT);
//
//vec3 winCoord = vec3(windowCoordinate[0], windowCoordinate[1], windowCoordinate[2]);
//
//vec3 winCoordLT = vec3(windowCoordinateLT[0], windowCoordinateLT[1], windowCoordinateLT[2]);
//vec3 winCoordLB = vec3(windowCoordinateLB[0], windowCoordinateLB[1], windowCoordinateLB[2]);
//vec3 winCoordRT = vec3(windowCoordinateRT[0], windowCoordinateRT[1], windowCoordinateRT[2]);
//vec3 winCoordRB = vec3(windowCoordinateRB[0], windowCoordinateRB[1], windowCoordinateRB[2]);
//
///*float xAppWin = 200 + x / 2;
//float yAppWin = 180 + (WIN_H - y) / 2.6;*/
//float x0 = 400 / (position.z - 1);
//float n = 2.718;
//n = pow(n, -1) * (position.z - 3);
//float x1 = 667 + 133 - (133 / (1 + n));
//float y1 = 500 + 85.828 - 85.828 / (1 + n);
//float y0 = 250 / (position.z - 1);
//float xAppWin = interpolation(x, 0, WIN_W, x0, x1);// 60 + x * 775 / WIN_W;
//float yAppWin = interpolation(WIN_H - y, 0, WIN_H, y0, y1);
//
//if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && obj->theRole == MAIN) { cout << "y0 " << y0 << " y1 " << y1 << endl; }
//
//mouseX = WIN_W - mouseX;
//mouseX = 133 - 133 / (1 + pow(2.718, (-1 * (position.z - 3)))) + 667; // (mouseX) * 118 / WIN_W + 344;
//mouseY = (mouseY) * 80 / WIN_H + 262;
//bool inPosition = obj->inPosition(xAppWin, yAppWin, winCoordLT, winCoordLB, winCoordRT, winCoordRB);
