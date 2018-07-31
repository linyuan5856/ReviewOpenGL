
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>


#define  SRC_WIDTH 800
#define	 SRC_HEIGHT 600

void SetFrameBufferSizeCallBack(GLFWwindow*window, int width, int height);
void EventHandle(GLFWwindow*window);

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
	if (window ==nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	    char* str=nullptr;
		
		std::cin >> str;;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, SetFrameBufferSizeCallBack);


	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	while (!glfwWindowShouldClose(window))
	{
		EventHandle(window);
		glClearColor(0.2, 0.3, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

}
