#include "Kontrol.hpp"
glm::vec3 posisi = glm::vec3(0, 0, 5);
glm::mat4 pandangan;
//sudut horizontal : ke arah -Z
float sudutHorizontal = 3.14f;
//sudut vertikal : 0, dr sudut pandang horizon
float sudutVertikal = 0.0f;
//sudut pandang awal
float bidangPandangAwal = 45.0f;

float kecepatan = 3.0f; // 3 unit/s
float kecepatanMouse = 0.005f;

float lastTime = glfwGetTime();
glm::vec3 depan, kanan, atas;

void hitungMatriksDariInput(GLFWwindow* win) {
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;
	double xpos, ypos;
	glfwGetCursorPos(win, &xpos, &ypos);

	//reset ke tengah
	glfwSetCursorPos(win, 1024 / 2, 768 / 2);

	//hitung orientasi baru
	sudutHorizontal += kecepatanMouse * deltaTime * float(1024 / 2 - xpos);
	sudutVertikal += kecepatanMouse * deltaTime * float(768 / 2 - ypos);

	//Arah: koordinat lingkaran ke koordinat kartesius
	depan = glm::vec3(
		cos(sudutVertikal) * sin(sudutHorizontal),
		sin(sudutVertikal),
		cos(sudutVertikal)* cos(sudutHorizontal)
	);

	kanan = glm::vec3(
		sin(sudutHorizontal - 3.14f / 2.0f),
		0,
		cos(sudutHorizontal - 3.14f / 2.0f)
	);

	atas = glm::cross(kanan, depan);

	//depan
	if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) {
		posisi += depan * deltaTime * kecepatan;
	}
	//bawah
	if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS) {
		posisi -= depan * deltaTime * kecepatan;
	}
	//kanan
	if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		posisi += kanan * deltaTime * kecepatan;
	}
	//kiri
	if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS) {
		posisi -= kanan * deltaTime * kecepatan;
	}

}
glm::mat4 ambilMatriksPandangan(){

	pandangan = glm::lookAt(
		posisi, // Camera is at (4,3,3), in World Space
		posisi + depan, // and looks at the origin
		atas // Head is up (set to 0,-1,0 to look upside-down)
	);
	return pandangan;
}


glm::mat4 ambilMatriksProyeksi() {
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f,
		100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	// Camera matrix
	return Projection;
}
