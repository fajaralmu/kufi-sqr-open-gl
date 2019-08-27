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
		void setVertexObj(VertexObj vertexOBJ);
		//virtual void loadTexture();
		float calculateDimension(int index, std::vector<glm::vec3> theVector);
		
		vec3 dimension;
		vec3 position = glm::vec3(0, 0, 10); //
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


		//identity
		bool initTexture = false;
		bool initBuffer = false;
		bool active = false;
		bool isDeleted = false;
		EntityRole theRole;
		int id;
		
		
	};
	static int staticID;

	
}

