#pragma once

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
#include <map>
#include <vector>

struct VertexObj {
	GLuint vertexID;
	std::vector < glm::vec3 > verticesArray;
	std::vector < glm::vec2 > uvsArray;
	std::vector < glm::vec3 > normalsArray;

};

