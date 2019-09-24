#include "Application.h"
#include <math.h>

namespace App {
	int texIdx = 0;// , c = 0;// , collideTimer = 0;

	Application::Application() {
		xpos = WIN_W / 2; 	ypos = WIN_H / 2;

		cout << "===========AHLAN WA SAHLAN FIE HADZAL BARNAMAJ==============" << endl;
		cout << "===========WELCOME TO THE APPLICATION=========== " << endl;
		cout << "Please insert cube dimension: ";
		cin >> cubeDimension;
		cout << endl;
		cout << "Cube dimension is >>" << cubeDimension << endl;
		cout << "Select the following type" << endl;
		cout << "1. Using top of cube" << endl;
		cout << "2. Using base of cube" << endl;
		cin >> layoutType;
		cout << endl;
		cout << "Generating app with layout >>" << layoutType << endl;
	}

	Application::~Application() {


	}

	void Application::mouseProcess(BaseEntity * obj, int b, int s, double mouse_x, double mouse_y)
	{
		float x = 1.0f - (2.0f * mouse_x) / WIN_W;// -1.0f;
		float y = /*1.0f - */(2.0f * mouse_y) / WIN_H - 1.0f;;
		float z = 1.0f;
		vec3 ray_nds = vec3(x, y, z);//normalized device coords
		printVector(ray_nds, "==>ray_nds");
		vec4 ray_clip = vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
		vec4 ray_eye = inverse(obj->projection) * ray_clip;
		ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
		printVector(ray_eye, "==>ray_eye");
		vec4 viewInverse = (inverse(obj->view) * ray_eye);
		vec3 ray_wor = vec3(viewInverse.x, viewInverse.y, viewInverse.z);
		// don't forget to normalise the vector at some point
		ray_wor = normalize(ray_wor);
		printVector(ray_wor, "==>ray WORLD");
		printVector(obj->position, "==>OBJ POS");
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
		mainTexID = loadBMP_custom("number.bmp");
		worldTexID = loadBMP_custom("brick.bmp");
		/*	mainVertObj = loadObjectFromFile("cube.obj");
			worldVertObj = loadObjectFromFile("cube.obj");*/

		glBindBuffer(GL_ARRAY_BUFFER, mainTexID);
		glBindBuffer(GL_ARRAY_BUFFER, worldTexID);
		/*glBindBuffer(GL_ARRAY_BUFFER, mainVertObj.vertexID);
		glBindBuffer(GL_ARRAY_BUFFER, worldVertObj.vertexID);*/

		VertexObj BaseVertObj = loadObjectFromFile("cube.obj");// , this->vertexArray, uvArray, normalArray);

		for (int i = 0; i < sizeof(textureNames) / sizeof(std::string); i++) {
			textureIDs[i] = loadBMP_custom(textureNames[i].c_str());
			/*TEX  & NORMAL BUFFER*/
			glBindBuffer(GL_ARRAY_BUFFER, textureIDs[i]);
			int colorBufferSize = BaseVertObj.uvsArray.size() * sizeof(vec2); //sizeof(g_color_buffer_data)
			glBufferData(GL_ARRAY_BUFFER, colorBufferSize, &BaseVertObj.uvsArray[0], GL_STATIC_DRAW);

			//glGenBuffers(1, &normalIDs[i]);//generate 1 buffer and the identifier in vertexBuffer
			//glBindBuffer(GL_ARRAY_BUFFER, normalIDs[i]);
			//int normalBufferSize = vertObj.normalsArray.size() * sizeof(vec3);// sizeof(g_vertex_buffer_data);
			//glBufferData(GL_ARRAY_BUFFER, normalBufferSize, &vertObj.normalsArray[0], GL_STATIC_DRAW);

		}
		/**
		* load texture for font
		*/
		for (int i = 0; i < sizeof(textureForTextNames) / sizeof(std::string); i++) {
			if (textureForTextNames[i] == "")
				continue;
			string texturePath = "text/" + textureForTextNames[i] + ".bmp";
			//cout << "loading :" << texturePath << endl;
			GLuint texID = loadBMP_custom(texturePath.c_str());
			/*TEX  & NORMAL BUFFER*/
			glBindBuffer(GL_ARRAY_BUFFER, texID);
			int colorBufferSize = BaseVertObj.uvsArray.size() * sizeof(vec2); //sizeof(g_color_buffer_data)
			glBufferData(GL_ARRAY_BUFFER, colorBufferSize, &BaseVertObj.uvsArray[0], GL_STATIC_DRAW);
			textTextureIDs.insert(pair<char, GLuint>(textureForTextNames[i].at(0), texID));
			cout << "LOADING ======>" << textureForTextNames[i].at(0) << endl;

		}

		objA = new AppObject("little-cube.obj", "number_.bmp");
		objA->theRole = Entity::MAIN;
		objA->textureID = mainTexID;
		objA->active = true;
		//objA->setVertexObj(mainVertObj);
		objA->intializeVertex();
		vec3 BaseDimension = vec3(2, 2, 2);
		objects.push_back(objA);
		float padding = 0.0;
		//init x count objs
		if (layoutType == 1) {
			createObject(1, cubeDimension, cubeDimension, BaseDimension, vec3(1, 1, 1), padding);
			createObject(cubeDimension, cubeDimension, 1, BaseDimension, vec3(1, 1, 1), padding);
			createObject(cubeDimension, 1, cubeDimension, BaseDimension, vec3(1, 1, 1), padding);

		}
		else
		{
			createObject(1, cubeDimension, cubeDimension, BaseDimension, vec3(cubeDimension, 1, 1), padding);
			//	createObject(cubeDimension, cubeDimension,1, BaseDimension, vec3(1, 1, 1), padding);
			createObject(cubeDimension, 1, cubeDimension, BaseDimension, vec3(1, cubeDimension, 1), padding);
			createObject(cubeDimension, cubeDimension, 1, BaseDimension, vec3(1, 1, cubeDimension), padding);
		}
		int begin = staticObjCount;
		for (int i = 0; i < staticObjCount; i++) {
			AppObject* staticA;
			staticA = new AppObject("cube.obj", "number_.bmp");
			staticA->textureID = textureIDs[2];
			staticA->position = vec3(begin - (i)*2.1, -19, 50);
			staticA->intializeVertex();
			staticA->staticObject = true;
			objects.push_back(staticA);

		}

		return true;
	}

	void Application::createObject(int xCount, int yCount, int zCount, vec3 BaseDimension, vec3 basePosition, double padding) {
		int posX = basePosition.x - 1;
		int posY = basePosition.y - 1;
		int posZ = basePosition.z - 1;
		printVector(basePosition, "CREATING CUBE LAYOUT");
		for (int x = posX; x < xCount + posX; x++)
			for (int y = posY; y < yCount + posY; y++)
				for (int z = posZ; z < zCount + posZ; z++)
				{
					AppObject * obj;
					obj = new AppObject("little-cube.obj", "number_.bmp");
					obj->textureID = worldTexID;
					//obj->setVertexObj(worldVertObj);
					obj->intializeVertex();
					obj->position.x = x * (BaseDimension.x + padding);
					obj->position.y = y * (BaseDimension.y + padding);
					obj->position.z += z * (BaseDimension.z + padding);

					objects.push_back(obj);
				}
	}

	void Application::printText(string text)
	{
		if (text.size() > staticObjCount) { return; }
		vector<int> staticObjectIdx;
		int runningI = 0;
		for (BaseEntity* obj : objects) {
			if (obj->staticObject) {
				staticObjectIdx.push_back(runningI);
				//clear text
				obj->textureID = textTextureIDs['_'];
			}
			runningI++;
			//obj->intializeVertex();
		}
		int textLength = text.size();
		for (int i = 0; i < textLength; i++) {
			objects[staticObjectIdx[i]]->textureID = textTextureIDs[text.at(i)];
		}
	}

	void Application::initBufferV2()
	{
		try {
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
		catch (exception * e) { cout << ("Exception :") << e->what() << endl; }
	}

	void Application::initShader()
	{
		programID = LoadShaders(vertexShaderFileName.c_str(), fragmentShaderFileName.c_str());
		glUseProgram(programID);
		getUniformsLocationFromShader();

	}

	void Application::addObject(BaseEntity * obj) { objects.push_back(obj); }

	void Application::removeAnObject(BaseEntity * obj)
	{
		for (int i = 0; i < objects.size(); i++)
			if (obj->id == objects[i]->id)
			{
				cout << "DELETE " << obj->id << endl;
				objects.erase(objects.begin() + i);
				break;
			}
	}

	void Application::getAllActiveObj()
	{
		activeObj.clear();
		for each (BaseEntity * obj in objects) { if (obj->theRole != MAIN && obj->active) { activeObj.push_back(obj); } }
	}

	bool Application::handleCollision(BaseEntity* mainObj, mat4 mvp)
	{
		/*collideTimer++;*/

		for each (AppObject* obj in objects)
		{
			bool isMain = obj->theRole == MAIN;
			if (isMain) {
				bool pressM = glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS;
				bool pressI = glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS;

				if (pressI)
				{   //reset mouse MOVEMENT
					printVector(obj->position, "CURRENT OBject position");
					obj->position = vec3(0, 0, 10);
					glfwSetCursorPos(window, WIN_W / 2, WIN_H / 2);
					printVector(obj->position, "RESET OBject position");
					getMouseMovement();
					printVector(direction, "CURRENT DIRECTION");
				}
				if (pointerMode)
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				else
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

				if (pressM) { pointerMode = !pointerMode; Sleep(5); }
				if (pointerMode) {
					movement = getMouseMovement(false);
					double div = ( (obj->position.z*obj->position.z)/10);
					double moveX = movement.x / div, moveY = movement.y / div;
					if (movement.z == 0) {
						obj->position.x -= moveX;
						obj->position.y += moveY;
					}else
						obj->position.z +=  movement.z / div;
					double base = 90;
					double zero = 0;
					/*if (obj->position.z < 0.0 || obj->position.z >= 90.0){
						obj->position.z = 10;
					}
					if (obj->position.x < -50||obj->position.x >= 50) {
						obj->position.x = 0;
					}
					if (obj->position.y < -50||obj->position.y >= 50) {
						obj->position.y = 0;
					}*/

				}
			}

			bool collide = mainObj->isCollide(obj) && !obj->staticObject;
			if ((collide || obj->active)) {
				obj->textureID = textureIDs[3];
				//	obj->initializeBuffer();
				if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS && !isMain) {
					Sleep(10);
					removeAnObject(obj);
					return true;
				}
				if ((collide) && obj->theRole == WORLD && glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
					Sleep(10);
					AppObject * newObj;
					newObj = new AppObject("cube.obj", "number_.bmp");
					newObj->position = obj->position;
					newObj->textureID = mainTexID;
					newObj->active = true;
					//newObj->setVertexObj(worldVertObj);
					newObj->intializeVertex();
					addObject(newObj);
					initBufferV2();
					return true;
				}

				if (collide && glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
					Sleep(10);
					mainObj->joinObject(obj, true, vec3(0, 0, 0));
					getUniformsLocationFromShader();
				}
				if (collide && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
					Sleep(10);
					cout << obj->id << " set active :" << !obj->active << endl;
					obj->active = !obj->active;
				}
			}

			if (obj->active && !collide && !obj->staticObject) { obj->textureID = mainTexID; }
			else if (!collide && !obj->staticObject) { obj->textureID = worldTexID; }
		}
		return false;
	}

	void Application::handleMotionKeyPress()
	{
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
		bool pressU = glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS;
		bool pressDel = glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS;
		bool pressEnd = glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS;

		if (init) {
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

		//delete INactive object
		if (pressDel) for each (AppObject* obj in objects) { if (!obj->active) obj->isDeleted = true; }

		//delete active object
		if (pressEnd) for each (AppObject* obj in objects) { if (obj->active) obj->isDeleted = true; }

		if (pressSpace) deltaTime *= 3;

		for each (AppObject* obj in objects)
		{
			if (obj->staticObject) continue;
			bool isMain = (obj->theRole == Entity::MAIN);

			if (pressUp) { obj->position += direction * deltaTime *speed; }
			if (pressDown) { obj->position -= direction * deltaTime *speed; }
			if (pressRight) { obj->position += rightMove * deltaTime *speed; }
			if (pressLeft) { obj->position -= rightMove * deltaTime *speed; }

			/*if (pressPageUp) { obj->position -= rightMove * deltaTime *speed; }
			if (pressPageDown) { obj->position -= rightMove * deltaTime *speed; }*/

			if (!isMain)
				continue;

			if (pressW) { obj->position.y += deltaTime; }
			if (pressS) { obj->position.y -= deltaTime; }
			if (pressQ) { obj->position.z += deltaTime; }
			if (pressE) { obj->position.z -= deltaTime; }
			if (pressA) { obj->position.x += deltaTime; }
			if (pressD) { obj->position.x -= deltaTime; }
			
			/*string zMove = "_"+ doubleToString(movement.z,4);*/
			string positionInfo = "x" + doubleToString(obj->position.x, 5) + "_y" + doubleToString(obj->position.y, 5) + "_z" + doubleToString(obj->position.z, 5);
			printText(positionInfo);
			//object operation
			if (pressU) {
				getAllActiveObj();
				obj->joinObjects(activeObj);
				Sleep(5);
			}

			if (pressN) {
				AppObject * newObj;
				newObj = new AppObject("cube-old.obj", "number.bmp");
				newObj->position = obj->position;
				newObj->textureID = mainTexID;
				//newObj->setVertexObj(worldVertObj);
				newObj->intializeVertex();
				addObject(newObj);
				initBufferV2();
				Sleep(5);
				break;
			}
			if (pressC) {
				if (obj->textureID == worldTexID)obj->textureID = mainTexID;
				else obj->textureID = (textureIDs[texIdx]);
				obj->initializeTextureBuffer();
				obj->initializeVertexAndNormalBuffer();
				cout << "pressC" << endl;

				texIdx++;
				if (texIdx >= 4) { texIdx = 0; }
				Sleep(5);
				break;
			}

		}

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
		glfwSetCursorPos(window, WIN_W / 2, WIN_H / 2);
		getMouseMovement();
		printText("2019 fajar");

		do {

			glEnable(GL_DEPTH_TEST); // z component
			glDepthFunc(GL_LESS); //accept fragment if it closer to the camera than the former one
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 0.4, 0);
			glfwGetCursorPos(window, &mouseX, &mouseY);

			handleMotionKeyPress();

			glEnableVertexAttribArray(0);/*1ST ATTRIBUTE BUFFER : VERTICES*/
			glEnableVertexAttribArray(1);/*2ND ATRIBUTE BUFFER: UV*/
			glEnableVertexAttribArray(2);/*3RD ATRIBUTE BUFFER: NORMALS */

			
			try {
				for each (AppObject* obj in objects)
				{
					if (obj == nullptr || obj->isDeleted) continue;

					mat4 model = glm::mat4(1.0f);
					//ViewModelProjection : mult of 3 matrices
					mat4 projection = glm::perspective(glm::radians(angle), aspectRatio, nearClippingPane, farClippingPane);

					vec3 staticDirection = vec3(
						cos(verticalAngleBase) * sin(horizontalAngleBase),
						sin(verticalAngleBase),
						cos(verticalAngleBase) * cos(horizontalAngleBase)
					);
					vec3 staticRightMove = vec3(
						sin(horizontalAngleBase - 3.14f / 2.0f),
						0,
						cos(horizontalAngleBase - 3.14f / 2.0f)
					);
					vec3 staticUp = glm::cross(staticRightMove, staticDirection);

					mat4 view = glm::lookAt(obj->position, obj->position + staticDirection, staticUp);
					if (!obj->staticObject) {
						//camera matrix
						view = glm::lookAt(obj->position, obj->position + direction, up);
					}
					//std::cout << position.x << "-" << position.y << "-" << position.z << "-" << direction.b << "-" << direction.g << endl;
					mat4 mvp = projection * view *model;
					obj->model = model;
					obj->direction = direction;
					obj->projection = projection;
					obj->view = view;
					obj->mvp = mvp;
					obj->mvpSet = true;

					if (obj->theRole == MAIN) {
						bool updateObjList = handleCollision(obj, mvp);
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
					try {
					GLsizei totalVertices = obj->vertexArray.size();//  sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]);
					
						glDrawArrays(GL_TRIANGLES, startingVertex, totalVertices);
					}
					catch (exception& e) { cout << ("Exception 1 :") << e.what() << endl; continue; }
				}
			}
			catch (exception& e) { cout << ("Exception 2 :") << e.what() << endl; continue; }
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

	GLdouble* Application::mat4ToDoubleArray(mat4 mat) {
		GLdouble arr[16];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				arr[i * 4 + j] = mat[i][j];
				//	cout << mat[i][j] <<" "<< i * 4 + j << endl;
			}
		}

		return arr;

	}

	void Application::getUniformsLocationFromShader() {
		matrixID = glGetUniformLocation(programID, "MVP");
		viewMatrixID = glGetUniformLocation(programID, "V");
		modelMatrixID = glGetUniformLocation(programID, "M");
		lightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	}

	bool justAdjusted = false;

	vec3 Application::getMouseMovement(bool sleep)
	{
		if (justAdjusted) {
			justAdjusted = false;
			return vec3();
		}
		double latestX = 0.0f;
		double latestY = 0.0f;
		glfwGetCursorPos(window, &latestX, &latestY);

		if (latestX<0 || latestX> WIN_W || latestY < 0 || latestY > WIN_H) {
			if (pointerMode) {
				glfwSetCursorPos(window, WIN_W / 2, WIN_H / 2);
				justAdjusted = true;
			}
			cout << " INVALID POSITION " << endl;
			return vec3();
		}

		if (sleep) printVector(vec3(mouseActualX, mouseActualY, 0), " current pos");
		if (sleep) printVector(vec3(latestX, latestY, 0), " latest pos");
		double deltaX = latestX - mouseActualX;
		double deltaY = latestY - mouseActualY;
		double base = (deltaX * deltaY) / 2;// == NAN ? 0 : (deltaX * deltaY) / 2;
		double zMove = base;
		if (zMove != 0) {
			deltaX = 0;
			deltaY = 0;
		}
		/*if (zMove < 0 || zMove>100) {
			zMove = 0;
		}
		if (zMove < 0 || zMove>100) {
			zMove = 0;
		}*/
		
		vec3 movement = vec3(deltaX, deltaY, zMove);
		if (sleep) printVector(movement, " MOVEMENT");
		mouseActualX = latestX; mouseActualY = latestY;
		if (sleep)  Sleep(100);
		return movement;
	}

}