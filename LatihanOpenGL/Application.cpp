#include "Application.h"

namespace App {
	int texIdx = 0;
	int c = 0;


	Application::Application()
	{
		xpos = WIN_W / 2;
		ypos = WIN_H / 2;

	}

	Application::~Application()
	{
	}


	bool App::Application::initWindow()
	{
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
		//	glfwMakeContextCurrent(window); // <-- make the context current before glViewport

			//glViewport(0, 0, WIN_W, WIN_H);

		std::cout << ("Window created.. ") << endl;
		glfwMakeContextCurrent(window); //Initialize GLEW
		glewExperimental = true;//Needed in core profile
		if (glewInit() != GLEW_OK) {
			fprintf_s(stderr, "Failed initialize GLEW");
			return false;
		}
		glfwSetCursorPos(window, WIN_W / 2, WIN_H / 2);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		std::cout << ("GLEW initialized.. ") << endl;

		AppObject * objA;
		mainTexID = loadBMP_custom("main_obj.bmp");
		worldTexID = loadBMP_custom("number.bmp");
		/*	mainVertObj = loadObjectFromFile("cube.obj");
			worldVertObj = loadObjectFromFile("cube.obj");*/

		glBindBuffer(GL_ARRAY_BUFFER, mainTexID);
		glBindBuffer(GL_ARRAY_BUFFER, worldTexID);
		/*glBindBuffer(GL_ARRAY_BUFFER, mainVertObj.vertexID);
		glBindBuffer(GL_ARRAY_BUFFER, worldVertObj.vertexID);*/


		for (int i = 0; i < 5; i++) {
			textureIDs[i] = loadBMP_custom(textureNames[i].c_str());
			glBindBuffer(GL_ARRAY_BUFFER, textureIDs[i]);

		}

		objA = new AppObject("cube.obj", "main_obj.bmp");
		objA->theRole = Entity::MAIN;
		objA->textureID = mainTexID;
		//objA->setVertexObj(mainVertObj);
		objA->intializeVertex();
		objects.push_back(objA);
		//init x count objs
		for (int x = 0; x < xCount; x++)
			for (int y = 0; y < yCount; y++)
				for (int z = 0; z < zCount; z++)
				{
					AppObject * obj;
					obj = new AppObject("cube.obj", "number.bmp");
					obj->textureID = worldTexID;
					//obj->setVertexObj(worldVertObj);
					obj->intializeVertex();
					obj->position.x = x * (obj->dimension.x + 0.3);
					obj->position.y = y * (obj->dimension.y + 0.3);
					obj->position.z += z * (obj->dimension.z + 0.3);

					objects.push_back(obj);
				}
		return true;
	}

	void Application::initBufferV2()
	{
		try {
			//for each (AppObject* obj in objects) {
			//	if (obj->initTexture == false)
			//	{
			//		//obj->loadTexture();
			//		obj->initTexture = true;
			//	}
			//}

			cout << "init buffer" << endl;
			for each (AppObject* obj in objects) {
				if (obj->initBuffer == false) {
					obj->initializeTextureBuffer();
					obj->initializeVertexAndNormalBuffer();
					obj->initBuffer = true;
				}
			}
			cout << "==init buffer" << endl;
		}
		catch (exception& e) {
			cout << ("Exception :") << e.what() << endl;

		}


	}

	void Application::initShader()
	{
		programID = LoadShaders(vertexShaderFileName.c_str(), fragmentShaderFileName.c_str());
		glUseProgram(programID);
		getUniformsLocationFromShader();

	}

	void Application::addObject(BaseEntity * obj)
	{
		objects.push_back(obj);
	}

	void Application::removeObject(BaseEntity * obj)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (obj->id == objects[i]->id)
			{
				objects.erase(objects.begin() + i);
				break;
			}
		}
	}

	int collideTimer = 0;

	bool Application::handleCollision(BaseEntity* mainObj)
	{
		collideTimer++;
		//return;
		//begin mouse
		double x, y;
		double xTemp, yTemp;
		glfwGetCursorPos(window, &x, &y);
		xTemp = x;
		yTemp = y;

		x = x / 32 - (WIN_W / 64);

		//	x /= 2.8;
		x *= -1;
		y = y / 32 - (WIN_H / 64);

		//	y /= 2.8;
			//end mouse
		for each (AppObject* obj in objects)
		{

			//mouse
			double x, y;
			double xTemp, yTemp;
			glfwGetCursorPos(window, &x, &y);

			//obj coord on viewport
			GLdouble model_view[16];
			glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
			GLdouble projection_mat[16];
			glGetDoublev(GL_PROJECTION_MATRIX, projection_mat);
			GLint viewPort[4];
			glGetIntegerv(GL_VIEWPORT, viewPort);

			float windowCoordinate[3];
			//
			float windowCoordinateLT[3];
			float windowCoordinateLB[3];
			float windowCoordinateRT[3];
			float windowCoordinateRB[3];

			int res = glhProjectf(obj->position.x, obj->position.y, obj->position.z,
				model_view, projection_mat, viewPort, windowCoordinate);
			//
			float halfDimensionX = obj->dimension.x / 2;
			float halfDimensionY = obj->dimension.y / 2;
			int resRB = glhProjectf(obj->position.x - halfDimensionX, obj->position.y + halfDimensionY, obj->position.z,
				model_view, projection_mat, viewPort, windowCoordinateRB);
			int resRT = glhProjectf(obj->position.x - halfDimensionX, obj->position.y - halfDimensionY, obj->position.z,
				model_view, projection_mat, viewPort, windowCoordinateRT);
			int resLB = glhProjectf(obj->position.x + halfDimensionX, obj->position.y + halfDimensionY, obj->position.z,
				model_view, projection_mat, viewPort, windowCoordinateLB);
			int resLT = glhProjectf(obj->position.x + halfDimensionX, obj->position.y - halfDimensionY, obj->position.z,
				model_view, projection_mat, viewPort, windowCoordinateLT);

			vec3 winCoord = vec3(windowCoordinate[0], windowCoordinate[1], windowCoordinate[2]);

			vec3 winCoordLT = vec3(windowCoordinateLT[0], windowCoordinateLT[1], windowCoordinateLT[2]);
			vec3 winCoordLB = vec3(windowCoordinateLB[0], windowCoordinateLB[1], windowCoordinateLB[2]);
			vec3 winCoordRT = vec3(windowCoordinateRT[0], windowCoordinateRT[1], windowCoordinateRT[2]);
			vec3 winCoordRB = vec3(windowCoordinateRB[0], windowCoordinateRB[1], windowCoordinateRB[2]);

			float xAppWin = 200 + x / 2;
			float yAppWin = 180 + (WIN_H - y) / 2.6;

			bool inPosition = obj->inPosition(xAppWin, yAppWin, winCoordLT, winCoordLB, winCoordRT, winCoordRB);

			if (obj->theRole == MAIN) {
				if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
				{
					printVector(winCoord, "===OBJ POS GLUPROJ CENTER");
					printVector(winCoordLT, "===OBJ POS GLUPROJ LT");
					printVector(winCoordLB, "===OBJ POS GLUPROJ LB");
					printVector(winCoordRT, "===OBJ POS GLUPROJ RT");
					printVector(winCoordRB, "===OBJ POS GLUPROJ RB");
					printVector(vec3(xAppWin, yAppWin, 0), "===MOUSE POS");
					cout << "IN POSITION : " << inPosition << endl;
					if (x >= winCoordLT.x && x <= winCoordRT.x) cout << "ok1" << endl;

					if (y <= winCoordLT.y &&y >= winCoordRB.y) cout << "ok2" << endl;
				}
				continue;
			}

			bool collide = mainObj->isCollide(obj);
			if ((collide || inPosition || obj->active)) {
				obj->textureID = mainTexID;
				//	obj->initializeBuffer();
				if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
					removeObject(obj);
					return true;
					break;
				}
				if (collideTimer > 20 && inPosition && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
					collideTimer = 0;
					cout << obj->id << " set active :" << !obj->active << " " << collideTimer << endl;
					obj->active = !obj->active;
					//return true;
			//		break;
				}

			}
			else {
				obj->textureID = worldTexID;
				//	obj->initializeBuffer();
			}
		}
		return false;
	}

	void Application::handleKeyPress()
	{
		c++;
		double currentTime = glfwGetTime();

		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;
		//printVector(position, "position");

		bool pressUp = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
		bool pressDown = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
		bool pressRight = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
		bool pressLeft = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
		bool pressO = glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
		bool pressSpace = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
		bool pressPageUp = glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS;
		bool pressPageDown = glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS;
		bool pressRALt = glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS;
		bool pressRCtrl = glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;
		bool pressENter = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
		bool pressBackSpace = glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS;
		bool pressW = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
		bool pressS = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
		bool pressA = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
		bool pressD = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
		bool pressQ = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;
		bool pressE = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
		bool pressN = glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS;
		bool pressC = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;
		bool pressI = glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS;

		if (init) {
			//	glfwGetCursorPos(window, &xpos, &ypos);
			cout << xpos << "," << ypos << endl;
			init = false;
		}
		//reset ke tengah
		ypos = WIN_H / 2; xpos = WIN_W / 2;

		int incrementBy = 30 + (pressSpace ? 30 : 0);

		ypos += (pressPageUp ? incrementBy : 0) + (pressPageDown ? -incrementBy : 0);
		xpos += (pressRALt ? incrementBy : 0) + (pressRCtrl ? -incrementBy : 0);

		//compute orientation
		horizontalAngle += mouseSpeed * deltaTime * float(WIN_W / 2 - xpos);
		verticalAngle += mouseSpeed * deltaTime * float(WIN_H / 2 - ypos);

		/*std::cout << horizontalAngle<< ", H increment: " << (mouseSpeed * deltaTime * float(WIN_W / 2 - xpos));
		std::cout << verticalAngle<< ", V increment: " << (mouseSpeed * deltaTime * float(WIN_H / 2 - ypos)) << endl;
		*/direction = vec3(
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



		if (pressSpace) {
			deltaTime *= 3;
		}
		for each (AppObject* obj in objects)
		{

			bool isMain = (obj->theRole == Entity::MAIN);
			//			bool inPosition = obj->inPosition(x, y);

			if (pressUp) {
				obj->position += direction * deltaTime *speed;
			}
			if (pressDown) {
				obj->position -= direction * deltaTime *speed;
			}
			if (pressRight) {
				obj->position += rightMove * deltaTime *speed;
			}
			if (pressLeft) {
				obj->position -= rightMove * deltaTime *speed;
			}
			/*if (c > 50)
				if (inPosition) {
					cout << "OBj =" << obj->id << " check position TRUE" << endl;

					obj->textureID = textureIDs[2];
					if (pressENter) {
						obj->active = true;
						obj->textureID = textureIDs[3];
					}
					if (pressBackSpace) {
						obj->active = false;
						obj->textureID = worldTexID;
					}
					obj->initializeTextureBuffer();
					obj->initializeVertexAndNormalBuffer();
					c = 0;
				}
				else {
					if (!obj->active) obj->textureID = worldTexID;
					else obj->textureID = textureIDs[3];

					obj->initializeTextureBuffer();
					obj->initializeVertexAndNormalBuffer();
					c = 0;
				}
				//MOUSE HOVER//

				*/
				//		cout << "MOUSE " << x << "," << y << endl;



						//	cout << " INPOSITION " << inPosition << endl;

						/*if (pressPageUp) {
							obj->position -= rightMove * deltaTime *speed;
						}
						if (pressPageDown) {
							obj->position -= rightMove * deltaTime *speed;
						}*/

			if (!isMain) continue;

			if (pressW) {
				obj->position.y += deltaTime;
			}
			if (pressS) {
				obj->position.y -= deltaTime;
			}
			if (pressQ) {
				obj->position.z += deltaTime;
			}
			if (pressE) {
				obj->position.z -= deltaTime;
			}
			if (pressA) {
				obj->position.x += deltaTime;
			}
			if (pressD) {
				obj->position.x -= deltaTime;
			}
			/*if (pressI) {
				printVector(obj->position, "MAIN POS");
				cout << "MOUSE " << x << "," << y << endl;

			}*/

			//object operation
			if (pressN && c > 50) {

				AppObject * newObj;
				newObj = new AppObject("cube.obj", "number.bmp");
				newObj->position = obj->position;
				newObj->textureID = worldTexID;
				//newObj->setVertexObj(worldVertObj);
				newObj->intializeVertex();
				addObject(newObj);
				initBufferV2();
				c = 0;
				break;
			}
			if (pressC && c > 50) {
				if (obj->textureID == worldTexID)obj->textureID = mainTexID;
				else obj->textureID = (textureIDs[texIdx]);
				obj->initializeTextureBuffer();
				obj->initializeVertexAndNormalBuffer();
				cout << "pressC" << endl;
				c = 0;
				texIdx++;
				if (texIdx >= 4) {
					texIdx = 0;
				}
				break;
			}

		}
		//if (pressUp || pressO || pressDown || pressRight || pressLeft) {
		//	std::cout << "control press" << endl;
		//	printVector(rightMove, "right move");


	}

	bool Application::initApp() {
		if (!glfwInit()) {
			fprintf_s(stderr, "Error Initialize GLFW");
			getchar();
			return false;
		}
		if (!initWindow()) {
			getchar();
			return false;
		}
		std::cout << "window init" << endl;

		return true;
	}

	int Application::run()
	{
		/*use the shader*/
		initShader();

		initBufferV2();

		//projection
		float angle = 45.0;
		float aspectRatio = (float)WIN_W / (float)WIN_H;
		float nearClippingPane = 0.1f;
		float farClippingPane = 100.0f; //display range: 0.1 - 100.0f
		GLenum type = GL_FLOAT;
		GLboolean isNormalized = GL_FALSE;
		GLsizei stride = 0;
		int arrayBufferOffset = 0;
		GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

		glViewport(0, 0, WIN_W, WIN_H);

		do {

			glEnable(GL_DEPTH_TEST); // z component
			glDepthFunc(GL_LESS); //accept fragment if it closer to the camera than the former one
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 0.4, 0);

			handleKeyPress();

			glEnableVertexAttribArray(0);/*1ST ATTRIBUTE BUFFER : VERTICES*/
			glEnableVertexAttribArray(1);/*2ND ATRIBUTE BUFFER: UV*/
			glEnableVertexAttribArray(2);/*3RD ATRIBUTE BUFFER: NORMALS */
			try {
				for each (AppObject* obj in objects)
				{



					string name = "OBJ-" + to_string(obj->id);
					//if (obj->theRole == MAIN)				printVector(obj->position, name);
					//model at origin
					mat4 model = glm::mat4(1.0f);
					//ViewModelProjection : mult of 3 matrices
					mat4 projection = glm::perspective(glm::radians(angle), aspectRatio, nearClippingPane, farClippingPane);
					//camera matrix
					mat4 view = glm::lookAt(obj->position, obj->position + direction, up);
					//std::cout << position.x << "-" << position.y << "-" << position.z << "-" << direction.b << "-" << direction.g << endl;
					mat4 mvp = projection * view * model;
					if (obj->theRole == MAIN) {

						////mouse
						//double x, y;
						//double xTemp, yTemp;
						//glfwGetCursorPos(window, &x, &y);

						////obj coord on viewport
						//GLdouble model_view[16];
						//glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
						//GLdouble projection_mat[16];
						//glGetDoublev(GL_PROJECTION_MATRIX, projection_mat);
						//GLint viewPort[4];
						//glGetIntegerv(GL_VIEWPORT, viewPort);

						//float windowCoordinate[3];
						////
						//float windowCoordinateLT[3];
						//float windowCoordinateLB[3];
						//float windowCoordinateRT[3];
						//float windowCoordinateRB[3];

						//int res = glhProjectf(obj->position.x, obj->position.y, obj->position.z,
						//	model_view, projection_mat, viewPort, windowCoordinate);
						////
						//float halfDimensionX = obj->dimension.x / 2;
						//float halfDimensionY = obj->dimension.y / 2;
						//int resRB = glhProjectf(obj->position.x - halfDimensionX, obj->position.y + halfDimensionY, obj->position.z,
						//	model_view, projection_mat, viewPort, windowCoordinateRB);
						//int resRT = glhProjectf(obj->position.x - halfDimensionX, obj->position.y - halfDimensionY, obj->position.z,
						//	model_view, projection_mat, viewPort, windowCoordinateRT);
						//int resLB = glhProjectf(obj->position.x + halfDimensionX, obj->position.y + halfDimensionY, obj->position.z,
						//	model_view, projection_mat, viewPort, windowCoordinateLB);
						//int resLT = glhProjectf(obj->position.x + halfDimensionX, obj->position.y - halfDimensionY, obj->position.z,
						//	model_view, projection_mat, viewPort, windowCoordinateLT);
						//
						//vec3 winCoord = vec3(windowCoordinate[0], windowCoordinate[1], windowCoordinate[2]);

						//vec3 winCoordLT = vec3(windowCoordinateLT[0], windowCoordinateLT[1], windowCoordinateLT[2]);
						//vec3 winCoordLB = vec3(windowCoordinateLB[0], windowCoordinateLB[1], windowCoordinateLB[2]);
						//vec3 winCoordRT = vec3(windowCoordinateRT[0], windowCoordinateRT[1], windowCoordinateRT[2]);
						//vec3 winCoordRB = vec3(windowCoordinateRB[0], windowCoordinateRB[1], windowCoordinateRB[2]);


						if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {

							/*printVector(winCoord, "===OBJ POS GLUPROJ CENTER");
							printVector(winCoordLT, "===OBJ POS GLUPROJ LT");
							printVector(winCoordLB, "===OBJ POS GLUPROJ LB");
							printVector(winCoordRT, "===OBJ POS GLUPROJ RT");
							printVector(winCoordRB, "===OBJ POS GLUPROJ RB");
							printVector(vec3(200 + x / 2, 180 + (WIN_H - y) / 2.6, 0), "===MOUSE POS");*/
							//		printMatrix(view, "OBJ VIEW");
								//	printMatrix(projection, "OBJ projection");
						}
						bool updateObjList = handleCollision(obj);
						if (updateObjList) break;
					}
					//test texture
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, obj->textureID);
					//	glUniform1i(TextureID, 0);
						//
						//send to currently bound shader
					glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
					glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &model[0][0]);
					glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &view[0][0]);
					glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);
					//					if (obj->theRole == MAIN) cout << "kakaka " << obj->id << ". " << obj->textureID << endl;

					glBindBuffer(GL_ARRAY_BUFFER, obj->vertexBufferID);
					glVertexAttribPointer(0, vertexCoordSize, type, isNormalized, stride, (void *)arrayBufferOffset);
					glBindBuffer(GL_ARRAY_BUFFER, obj->textureID);
					glVertexAttribPointer(1, uvCoordSize, type, isNormalized, stride, (void *)arrayBufferOffset);
					glBindBuffer(GL_ARRAY_BUFFER, obj->normalbufferID);
					glVertexAttribPointer(2, normalCoordSize, type, isNormalized, stride, (void *)arrayBufferOffset);

					/*DRAW*/
					//triangle
					GLint startingVertex = 0;
					GLsizei totalVertices = obj->vertexArray.size();//  sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]);
					glDrawArrays(GL_TRIANGLES, startingVertex, totalVertices);
				}
			}
			catch (exception& e) {
				cout << ("Exception :") << e.what() << endl;
				continue;
			}
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);

			//swap buffer
			glfwSwapBuffers(window);
			glfwPollEvents();
		} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
			&& glfwWindowShouldClose(window) == 0);
		//	getchar();
		return 0;
	}

	void Application::getUniformsLocationFromShader() {
		matrixID = glGetUniformLocation(programID, "MVP");
		viewMatrixID = glGetUniformLocation(programID, "V");
		modelMatrixID = glGetUniformLocation(programID, "M");
		lightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	}

}