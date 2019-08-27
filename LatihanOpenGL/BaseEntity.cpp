#include "BaseEntity.h"
#include "VectorUtil.hpp"
using namespace std;

namespace Entity {

	BaseEntity::BaseEntity()
	{
		this->theRole = WORLD;
		isDeleted = false;
		id = Entity::staticID;
		Entity::staticID++;
	}

	BaseEntity::~BaseEntity()
	{
	}

	void BaseEntity::init()
	{
		//		loadVertex(); //for computing dimension
		initTexture = false;
		initBuffer = false;
		active = false;
	}

	void BaseEntity::initializeTextureBuffer()
	{
		/*TEX  & NORMAL BUFFER*/
		glBindBuffer(GL_ARRAY_BUFFER, textureID);
		int colorBufferSize = uvArray.size() * sizeof(vec2); //sizeof(g_color_buffer_data)
		glBufferData(GL_ARRAY_BUFFER, colorBufferSize, &uvArray[0], GL_STATIC_DRAW);

	}

	void BaseEntity::intializeVertex()
	{
		std::string vp = vertPath;
		VertexObj vertObj = loadObjectFromFile(vp.c_str());// , this->vertexArray, uvArray, normalArray);
		setVertexObj(vertObj);
		float width, height, tick;
		if (1) {
			width = calculateDimension(0, vertexArray);
			height = calculateDimension(1, vertexArray);
			tick = calculateDimension(2, vertexArray);

			dimension = vec3(width, height, tick);
			//	VECTORUTIL_HPP::printVector(dimension, "DIMENSION OBJ-" + to_string(id));

		}

	}

	void BaseEntity::initializeVertexAndNormalBuffer()
	{

		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		int vertexBufferSize = vertexArray.size() * sizeof(vec3);// sizeof(g_vertex_buffer_data);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, &vertexArray[0], GL_STATIC_DRAW);//give the vertices to OpenGL

		glGenBuffers(1, &normalbufferID);//generate 1 buffer and the identifier in vertexBuffer
		glBindBuffer(GL_ARRAY_BUFFER, normalbufferID);
		int normalBufferSize = normalArray.size() * sizeof(vec3);// sizeof(g_vertex_buffer_data);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, &normalArray[0], GL_STATIC_DRAW);
	}

	/*void BaseEntity::changeTexture(std::string filePath)
	{
		this->texPath = filePath;
		loadTexture();
	}*/

	bool BaseEntity::isCollide(BaseEntity * obj)
	{
		bool collide = false;
		vec3 objPos = obj->position;

		if (objPos.x >= position.x &&position.x >= objPos.x - obj->dimension.x) {
			if (objPos.y <= position.y &&position.y <= objPos.y + obj->dimension.y) {

				if (objPos.z >= position.z &&position.z >= objPos.z - obj->dimension.z) {
					collide = true;
				}
			}
		}



		return collide;
	}

	bool BaseEntity::inPosition(float x, float y, vec3 objLT, vec3 objLB, vec3 objRT, vec3 objRB )
	{
		bool inPos = false;
		//printVector(vec3(x, y, 0), "MOUSE++POS");
		//TODO: rotation operation
		if (x >= objLT.x && x <= objRT.x) {

			if (y <= objLT.y &&y >= objLB.y)
			{
				inPos = true;
			}
		}
		return inPos;
	}

	void BaseEntity::setVertexObj(VertexObj vertexOBJ)
	{
		normalArray = vertexOBJ.normalsArray;
		uvArray = vertexOBJ.uvsArray;
		vertexArray = vertexOBJ.verticesArray;
		vertexBufferID = vertexOBJ.vertexID;
	}

	//void BaseEntity::loadTexture()
	//{
	//	int formerTexID = textureID;
	//	std::string tp = texPath;
	//	textureID = loadBMP_custom(tp.c_str());
	//	cout <<id<< ".texttureID from: "<< formerTexID<<" to " << textureID << endl;
	//	//glGenBuffers(1, &textureID);
	//	cout <<"load texture"<< textureID << endl;
	////	glActiveTexture(GL)
	//	//textureID = loadDDS("uvmap.dds");
	//}
	float BaseEntity::calculateDimension(int index, vector<vec3> theVector)
	{
		float max = 0;
		float min = 0;

		switch (index)
		{
		case 0:
			min = theVector[0].x;
			break;
		case 1:
			min = theVector[0].y;
			break;
		case 2:
			min = theVector[0].z;
			break;
		default:
			break;
		}

		for (int i = index; i < theVector.size(); i += 3)
		{
			float val = 0;
			switch (index)
			{
			case 0:
				val = theVector[i].x;
				break;
			case 1:
				val = theVector[i].y;
				break;
			case 2:
				val = theVector[i].z;
				break;
			default:
				break;
			}

			//cout << "xVAL: " << val << endl;
			if (val >= max) {
				max = val;
			}
			if (val <= min) {
				min = val;
			}
		}
		//cout << index << " max " << max << " min " << min << "=" << (max - min) << endl;
		return  max - min;

	}
}

