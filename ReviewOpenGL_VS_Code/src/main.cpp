#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

const int SCW = 800;
const int SCH = 600;

void SetFrameBufferSizeCallBack(GLFWwindow *, int, int);
void windowEventHandle(GLFWwindow *);

int main(int argc, char const *argv[])
{
    int res = glfwInit();
    if (res = GLFW_FALSE)
    {
        std::cout << "glfw init failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCW, SCH, "Opengl", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Creat Window Failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, SetFrameBufferSizeCallBack);

    int loadRes = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if (loadRes == GL_FALSE)
    {
        std::cout << "Glad loaderFailed" << std::endl;
        glfwTerminate();
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        windowEventHandle(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.3, 0.2, 1.0);
    };

    glfwTerminate();
    return 0;
}

void SetFrameBufferSizeCallBack(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void windowEventHandle(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}