
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <Shader.h>

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


	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	Shader triangleShader("trianglevs.glsl","trianglefs.glsl");
	
	float triangleVertices[]={
	     -0.5,-0.5,0.0,  1.0,0.0,0.0,
		  0.0,0.5,0.0,   0.0,1.0,0.0,
		  0.5,-0.5,0.0 ,  0.0,0.0,1.0,
		};

	GLuint VAO, VBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window))
	{
		EventHandle(window);
		glClearColor(0.2, 0.3, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		triangleShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
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
