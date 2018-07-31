
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Model.h>

#define  SRC_WIDTH 800
#define	 SRC_HEIGHT 600

float Cubevertices[] = {
	// positions          // normals           // texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

void SetFrameBufferSizeCallBack(GLFWwindow*window, int width, int height);
void EventHandle(GLFWwindow*window);
void SetCursorPosCallBack(GLFWwindow*, double, double);
void Setscroll_callback(GLFWwindow* window, double xoffset, double yoffset);
GLuint LoadTexture(const char*path);

glm::vec3 CameraPos(0.0, 0.0, 3.0);
glm::vec3 CameraFront(0.0, 0.0, -1.0);
glm::vec3 CameraUp(0.0, 1.0, 0.0);

glm::vec3 LightPos(1.2, 1.0, 2.0);

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

	Shader lampshader("lampVs.glsl", "lampFs.glsl");
	Shader cubeshader("cubeVs.glsl", "cubeFs.glsl");

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cubevertices), Cubevertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	GLuint diffuseTex = LoadTexture("../Res/Texture/container2.png");

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		EventHandle(window);
		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.05, 0.05, 0.05, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		cubeshader.use();
		glm::mat4 view = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SRC_WIDTH / (float)SRC_HEIGHT, 0.1f, 100.0f);
		cubeshader.setMat4("view", view);
		cubeshader.setMat4("projection", projection);
		cubeshader.setVec3("viewPos", CameraPos);

		cubeshader.setVec3("dirlight.lightDir",glm::vec3(-4.0,-2.0,-1.0));
		cubeshader.setVec3("dirlight.lightColor", glm::vec3(1.0, 1.0, 1.0));

		cubeshader.setVec3("pointlight.lightPos", LightPos);
		cubeshader.setVec3("pointlight.lightColor", glm::vec3(1.0, 0.0, 0.0));
		cubeshader.setFloat("pointlight.kc", 1.0);
		cubeshader.setFloat("pointlight.kl", 0.09);
		cubeshader.setFloat("pointlight.kq", 0.032);

		cubeshader.setVec3("spotlight.lightPos", CameraPos);
		cubeshader.setVec3("spotlight.direction", CameraFront);
		cubeshader.setVec3("spotlight.lightColor", glm::vec3(1.0, 1.0, 1.0));
		cubeshader.setFloat("spotlight.cutoff",glm::cos(glm::radians(15.0f)));
		cubeshader.setFloat("spotlight.kc", 1.0);
		cubeshader.setFloat("spotlight.kl", 0.09);
		cubeshader.setFloat("spotlight.kq", 0.032);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTex);
		glBindVertexArray(VAO);
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model(1.0);
			model = glm::translate(model, cubePositions[i]);
			float angle = i * 20.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0, 0.2, 0.5));
			cubeshader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lampshader.use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, LightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lampshader.setMat4("model",model);
		lampshader.setMat4("view", view);
		lampshader.setMat4("projection", projection);
		lampshader.setVec3("LightColor", glm::vec3(1.0, 0.0, 0.0));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(GL_NONE);


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

GLuint LoadTexture(const char * path)
{
	stbi_set_flip_vertically_on_load(GL_TRUE);
	GLuint texture;
	glGenTextures(1, &texture);
	GLint widht, height, colorChannel;
	GLubyte*data = stbi_load(path, &widht, &height, &colorChannel, 0);
	if (data != nullptr)
	{

		glBindTexture(GL_TEXTURE_2D, texture);
		GLint format = GL_RGB;
		if (colorChannel == 1)
		{
			format = GL_RED;
		}
		else if (colorChannel == 3)
		{
			format = GL_RGB;
		}
		else
		{
			format = GL_RGBA;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, widht, height, GL_NONE, format, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	}
	else
	{
		std::cout << stbi_failure_reason() << std::endl;
	}


	return texture;
}
