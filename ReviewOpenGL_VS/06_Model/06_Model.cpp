
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Model.h>

#define  SRC_WIDTH 1920
#define	 SRC_HEIGHT 1080

void SetFrameBufferSizeCallBack(GLFWwindow*window, int width, int height);
void EventHandle(GLFWwindow*window);
void SetCursorPosCallBack(GLFWwindow*, double, double);
void Setscroll_callback(GLFWwindow* window, double xoffset, double yoffset);

glm::vec3 CameraPos(0.0, 0.0, 3.0);
glm::vec3 CameraFront(0.0, 0.0, -1.0);
glm::vec3 CameraUp(0.0, 1.0, 0.0);

float lastTime;
float deltaTime;

float LastX, LastY;
bool firstTime = true;
float yaw = -90;
float pitch;
float fov = 45.0f;
int main()
{
	GLint result = glfwInit();
	if (result == GLFW_FALSE) {
		std::cout << "Create Window Failed" << std::endl; return -1;
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MAJOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow*window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "OPENGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		char* str = nullptr;

		std::cin >> str;;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, SetFrameBufferSizeCallBack);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, SetCursorPosCallBack);
	glfwSetScrollCallback(window, Setscroll_callback);


	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	Shader shader("modelvs.glsl", "modelfs.glsl");
	Model objModel("../Res/objects/nanosuit/nanosuit.obj");

	while (!glfwWindowShouldClose(window))
	{
		EventHandle(window);
		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.05, 0.05, 0.05, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.use();
		glm::mat4 model(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::rotate(model, glm::radians((float)glfwGetTime()) * 10, glm::vec3(0.0, 1.0, 0.0));
		model = glm::scale(model, glm::vec3(0.2));
		glm::mat4 view = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SRC_WIDTH / (float)SRC_HEIGHT, 0.1f, 100.0f);

		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);
		objModel.Draw(shader);


		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}

void SetFrameBufferSizeCallBack(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void EventHandle(GLFWwindow * window)
{
	float speed = 0.45f;
	speed *= deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		CameraPos += speed * CameraFront;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		CameraPos -= speed * CameraFront;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		CameraPos += speed * glm::normalize(glm::cross(CameraUp, CameraFront - CameraPos));
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		CameraPos -= speed * glm::normalize(glm::cross(CameraUp, CameraFront - CameraPos));
}

void SetCursorPosCallBack(GLFWwindow *window, double x, double y)
{
	if (firstTime)
	{
		LastX = x;
		LastY = y;
		firstTime = false;
		return;
	}

	float sensitivity = 0.05f;
	float deltaX = (x - LastX)*sensitivity;
	float deltaY = (LastY - y)*sensitivity;
	LastX = x;
	LastY = y;

	yaw += deltaX;
	pitch += deltaY;

	float yawR = glm::radians(yaw);
	float pitchR = glm::radians(pitch);
	glm::vec3 dir(1.0);
	dir.x = glm::cos(yawR)*glm::cos(pitchR);
	dir.y = glm::sin(pitchR);
	dir.z = glm::sin(yawR)*glm::cos(pitchR);

	CameraFront = glm::normalize(dir);
}

void Setscroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}