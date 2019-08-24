// Include standard headers
#include <stdio.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <string.h>

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <vector>
#include "common\ResourceLoader.hpp"

using namespace glm;
using namespace std;
GLuint loadBMP_custom(const char * imagepath) {
	const int elementCount = 54;

	unsigned char header[elementCount]; //bmp file begins with 54-bytes header
	unsigned int dataPos; //position int the file where actual data begin
	unsigned int width, height, imageSize;
	//actual RGB data
	unsigned char * data;

	//OPEN FILE
	char* mode = "rb";
	FILE * file = fopen(imagepath, mode);
	if (!file) {
		printf_s("Image cannot be opened\n");
		return 0;
	}
	cout << "Image " << imagepath << " opened" << endl;
	int elementSize = 1;
	//check header
	if (fread(header, elementSize, elementCount, file) != elementCount) {
		printf_s("Not a correct BMP file (1)\n");
		return 0;
	}
	//check if header 0-1 == B-M
	if (header[0] != 'B' || header[1] != 'M') {
		printf_s("Not a correct BMP file (2)\n");
		return 0;
	}

	cout << "BMP file is valid" << endl;
	//read in from byte array
	dataPos = *(int*)&header[0x0A];
	imageSize = *(int*)&header[0x22];
	width = *(int*)&header[0x12];
	height = *(int*)&header[0x16];

	//if missformated
	if (dataPos == 0) dataPos = elementCount;
	if (imageSize == 0) imageSize = width * height * 3;

	//create buffer
	data = new unsigned char[imageSize];
	//read actual data from file
	fread(data, elementSize, imageSize, file);
	cout << "Data: " << data << endl;
	fclose(file);

	//generate one openGL texture
	GLuint textureID;
	int size = 1;
	glGenBuffers(1, &textureID);
	cout << "glGenBuffers: " << textureID << endl;
	glGenTextures(size, &textureID);
	cout << "glGenTextures: " << textureID << endl;

	glBindTexture(GL_TEXTURE_2D, textureID); //bind the newly created texture

	//give image to openGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;





}

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}
	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);
	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);
	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL,
			&FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}
	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
}

GLuint loadDDS(const char * imagepath)
{
	unsigned char header[124];

	FILE * file;
	//open file
	file = fopen(imagepath, "rb");
	if (file == NULL) {
		printf_s("error opening file \n");
		return 0;
	}

	//verify file type
	char filecode[4];
	cout << "filecode init" << std::string(filecode) << std::endl;
	fread(filecode, 1, //buffer size
		4, //element count
		file);
	char type[3] = {
		filecode[0] , filecode[1] , filecode[2]
	};
	std::string typeStr = std::string(type);

	bool compare = toupper(typeStr[0]) == 'D' && toupper(typeStr[1]) == 'D' &&toupper(typeStr[2]) == 'S';
	cout << "COMPARE: " << compare << " " << filecode[0] << filecode[1] << filecode[2] << endl;
	string msg = "file type :" + typeStr + "\n";
	printf_s(msg.c_str());
	if (!compare) {
		fclose(file);
		printf_s("WRONG dds type\n");
		return 0;
	}

	//get surface description
	fread(&header, 124, 1, file);

	unsigned int height = *(unsigned int*)&header[8];
	unsigned int width = *(unsigned int*)&header[12];
	unsigned int linearSize = *(unsigned int*)&header[16];
	unsigned int mipMapCount = *(unsigned int*)&header[24];
	unsigned int fourCC = *(unsigned int*)&header[80];

	unsigned char * buffer;
	unsigned int bufsize;

	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	if (buffer == nullptr) {
		printf_s("buffer is nullptr");
		return 0;
	}
	fread(buffer, 1, bufsize, file);
	fclose(file);

	unsigned int componenets = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;

	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	//create texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	//bind the new texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	//fill each mimpmap one after another
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	//load mipmaps
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}
	free(buffer);


	return textureID;
}

bool loadObjectFromFile(
	const char * path,
	std::vector < glm::vec3 > & out_vertices,
	std::vector < glm::vec2 > & out_uvs,
	std::vector < glm::vec3 > & out_normals
) {
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<vec3> temp_vertices;
	vector<vec2> temp_uv;
	vector<vec3> temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf_s("Error opening obj file\n");
		return false;
	}

	while (1) {
		char lineHeader[128];
		//read 1st word of the line
		int res = fscanf(file, "%s", lineHeader);

		if (res == EOF) { //eof = end of file
			break;
		}

		//parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uv.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]
				);
			if (matches != 9) {
				printf("file cannot be read.. \n");
				return false;

			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);


		}

	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		vec2 uv = temp_uv[uvIndex - 1];
		out_uvs.push_back(uv);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}
	cout << "OK" << endl;
	fclose(file);
	return true;
}