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
		setDimension();

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
		glBufferData(GL_ARRAY_BUFFER, normalBufferSize, &normalArray[0], GL_STATIC_DRAW);

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
		vec3 objDim = obj->dimension;

		/*if (objPos.x >= position.x &&position.x >= objPos.x - obj->dimension.x)
			if (objPos.y <= position.y &&position.y <= objPos.y + obj->dimension.y)
				if (objPos.z >= position.z &&position.z >= objPos.z - obj->dimension.z)
					collide = true;*/
		if (position.x + dimension.x / 2 >= objPos.x - objDim.x / 2 &&
			position.x - dimension.x / 2 <= objPos.x + objDim.x / 2)
			if (
				position.y + dimension.y / 2 >= objPos.y - objDim.y / 2 &&
				position.y - dimension.y / 2 <= objPos.y - objDim.y / 2)
				collide = true;
		return collide;
	}

	bool BaseEntity::inPosition(float x, float y, vec3 objLT, vec3 objLB, vec3 objRT, vec3 objRB)
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

	bool BaseEntity::inPositionV2(float x, float y, vec3 objLT, vec3 objLB, vec3 objRT, vec3 objRB)
	{
		bool inPos = false;
		//printVector(vec3(x, y, 0), "MOUSE++POS");
		//TODO: rotation operation
		if (x <= objLT.x && x >= objRT.x) {

			if (y >= objLT.y &&y <= objLB.y)
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

	void BaseEntity::joinObject(BaseEntity * obj, bool resetObjProperty, vec3 baseDistance)
	{
		vec3 distanceXX;
		vec3 distance = this->position - obj->position;
		if (baseDistance.x == 0 && baseDistance.y == 0 && baseDistance.z == 0) {
			cout << "BASE DISTANCE INVALID" << endl;
			distanceXX = this->position - obj->position;
		}
		else {
			distanceXX = baseDistance;
			cout << "VALID BASE DISTANCE" << endl;
		}
		printVector(distanceXX, "DISTANCE");
		vector<vec3> objVertArray = obj->vertexArray;
		for (int i = 0; i < objVertArray.size(); i++) {
			objVertArray[i].x += distance.x;
			objVertArray[i].y += distance.y;
			objVertArray[i].z += distance.z;
			this->vertexArray.push_back(objVertArray[i]);
		}
		vector<vec2> objUVArray = obj->uvArray;
		for (int i = 0; i < objUVArray.size(); i++) {
			objUVArray[i].x += distanceXX.x;
			objUVArray[i].y += distanceXX.y;

			this->uvArray.push_back(objUVArray[i]);
		}
		vector<vec3> objNormalArray = obj->normalArray;
		for (int i = 0; i < objNormalArray.size(); i++) {
			objNormalArray[i].x -= distanceXX.x;
			objNormalArray[i].y -= distanceXX.y;
			objNormalArray[i].z -= distanceXX.z;
			this->normalArray.push_back(objNormalArray[i]);
		}
		if (resetObjProperty) {
			vec3 oldDim = dimension;
			vec3 oldPos = position;
			setDimension();
			bool minX = distance.x < 0;
			bool minY = distance.y < 0;
			bool minZ = distance.z < 0;
			
			initializeVertexAndNormalBuffer();
			initializeTextureBuffer();

			/*position.x += (dimension.x - oldDim.x) / 2 * (minX?-1:1);
			position.y += (dimension.y - oldDim.y) / 2 * (minY ? -1 : 1);
			position.z += (dimension.z - oldDim.z) / 2 * (minZ? -1 : 1);
			printVector(oldDim, "BEFORE DIMENSION " + id);
			printVector(oldPos, "BEFORE POS");
			printVector(dimension, "AFTER DIMENSION " + id);
			printVector(position, "AFTER POS");
*/

		}

	}

	void BaseEntity::joinObjects(std::vector<BaseEntity*> objects)
	{
		BaseEntity* currObj = this;
		for each (BaseEntity* obj in objects)
		{
			joinObject(obj, true, this->position - obj->position);
			currObj = obj;
		}
		/*initializeVertexAndNormalBuffer();
		initializeTextureBuffer();
		setDimension();*/
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
	void BaseEntity::setDimension()
	{
		float width, height, tick;

		width = calculateDimension(0, vertexArray);
		height = calculateDimension(1, vertexArray);
		tick = calculateDimension(2, vertexArray);

		dimension = vec3(width, height, tick);

	}
}

