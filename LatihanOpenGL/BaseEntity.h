#pragma once
#include "libs.hpp"
#include "EntityRole.hpp"
#include "common\ResourceLoader.hpp"
#include <string>
#include <string.h>
using namespace glm;
namespace Entity {

	class BaseEntity
	{

	public:
		BaseEntity();
		~BaseEntity();
		virtual void init();
		virtual void initializeTextureBuffer();
		void intializeVertex();
		void initializeVertexAndNormalBuffer();
		//void changeTexture(std::string filePath);
		bool isCollide(BaseEntity* obj);
		bool inPosition(float x, float y, vec3 objLT, vec3 objLB, vec3 objRT, vec3 objRB);
		bool inPositionV2(float x, float y, vec3 objLT, vec3 objLB, vec3 objRT, vec3 objRB);
		void setVertexObj(VertexObj vertexOBJ);
		void joinObject(BaseEntity * obj, bool resetObjProperty, vec3 distance);
		void joinObjects(std::vector<BaseEntity *> objects);
		//virtual void loadTexture();
		float calculateDimension(int index, std::vector<glm::vec3> theVector);
		void setDimension();

		vec3 dimension, direction;
		vec3 position = glm::vec3(0, 0, 10); //
		mat4 model; mat4 projection; mat4 view;
		std::vector<glm::vec3> vertexArray, normalArray;
		std::vector<glm::vec2> uvArray;
		BaseEntity::GLuint uvbuffer;
		GLuint normalbufferID;
		//GLuint vertexbufferID;
		GLuint vertexArrayID;
		GLuint uvArrayID;
		GLuint textureID;
		GLuint vertexBufferID; //identify vertexBuffer
		std::string texPath;
		std::string vertPath;
		mat4 mvp;
		bool mvpSet = false;


		//identity
		bool staticObject = false;
		bool initTexture = false;
		bool initBuffer = false;
		bool active = false;
		bool isDeleted = false;
		EntityRole theRole;
		int id;


	};
	static int staticID;


}

