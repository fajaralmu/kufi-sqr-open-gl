#include "loadOBJ.hpp"



bool loadOBJ(const char* namafile, vector<glm::vec3> &vertex_out, vector<glm::vec2> &uv_out, vector<glm::vec3> &normal_out) {
	vector<glm::vec3> vertex_array_temp;
	vector<glm::vec2> uv_array_temp;
	vector<glm::vec3> normal_array_temp;

	vector<unsigned int> indexVertices, indexUVs, indexNormals;

	FILE * file = fopen(namafile, "r");

	if (file == NULL) {
		printf("tidak bisa membuka file");
		return false;
	}
	else {
		cout << "ada file" << endl;
	}
	//baca file sampai bawah
	while (1) {
		char lineHeader[128];
		//ambil huruf pertama dalam garis
		int res = fscanf(file, "%s", lineHeader);
		//fscanf(file, "%s", lineHeader);
		if (res == EOF) {
			break;
		}
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertex_array_temp.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv_array_temp.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normal_array_temp.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			string vertex1, vertex2, vertex3;
			unsigned int indexVertex[3], indexUV[3], indexNormal[3];
			int cocok = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &indexVertex[0], &indexUV[0], &indexNormal[0],
				&indexVertex[1], &indexUV[1], &indexNormal[1], &indexVertex[2], &indexUV[2], &indexNormal[2]);
			if (cocok != 9) {
				printf("Tidak bisa memproses obj");
				return false;
			}
			indexVertices.push_back(indexVertex[0]);
			indexVertices.push_back(indexVertex[1]);
			indexVertices.push_back(indexVertex[2]);
			indexUVs.push_back(indexUV[0]);
			indexUVs.push_back(indexUV[1]);
			indexUVs.push_back(indexUV[2]);
			indexNormals.push_back(indexNormal[0]);
			indexNormals.push_back(indexNormal[1]);
			indexNormals.push_back(indexNormal[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}
	for (unsigned int i = 0; i < indexVertices.size(); i++) {
		unsigned int indexVertex = indexVertices[i];
		glm::vec3 vertex = vertex_array_temp[indexVertex - 1];
		vertex_out.push_back(vertex);
		//cout << vertex.x <<" "<<vertex.y<<" "<<vertex.z << endl;
	}
	for (unsigned int i = 0; i < indexUVs.size(); i++) {
		unsigned int indexUV = indexUVs[i];
		glm::vec2 uv = uv_array_temp[indexUV - 1];
		uv_out.push_back(uv);
		//cout << uv.x << " " << uv.y << endl;
	}
	for (unsigned int i = 0; i < indexNormals.size(); i++) {
		unsigned int indexNormal = indexNormals[i];
		glm::vec3 normal = normal_array_temp[indexNormal - 1];
		normal_out.push_back(normal);
	}
	fclose(file);
	return true;
}
