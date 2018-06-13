#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

#define  HEIGHT 600
#define  WIDTH 800
using namespace std;

float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
};

const char *vShaderStr = R"(
  #version 330 core
  layout(location=0) in vec3 pos;

  void main(){
  gl_Position=vec4(pos,1.0f);
})";

const char *fShaderStr = R"(
  #version 330 core
  out vec4 fragColor;

  void main(){
  fragColor=vec4(1.0f,0.5f,0.2f,1.0f);
}
)";

void setBufferSizeCallBack(GLFWwindow *, int, int);

void processInput(GLFWwindow *window);

void setBufferSizeCallBack(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

GLuint InitShader();

GLuint InitShader() {
    GLuint vShader, fShader, shaderProgramer;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderStr, nullptr);
    glCompileShader(vShader);

    GLint success;
    char infoLog[512];
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, sizeof(infoLog), nullptr, infoLog);
        cout << "Vertex Shader Compile Failed-->  " << infoLog << endl;
    }


    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderStr, nullptr);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, sizeof(infoLog), nullptr, infoLog);
        cout << "Fragment Shader Compile Failed-->  " << infoLog << endl;
    }


    shaderProgramer = glCreateProgram();
    glAttachShader(shaderProgramer, vShader);
    glAttachShader(shaderProgramer, fShader);
    glLinkProgram(shaderProgramer);
    glGetProgramiv(shaderProgramer , GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramer , 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return shaderProgramer;
}

int main() {

    int res = glfwInit();
    if (res == GLFW_FALSE) {
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "ReviewOPENGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, setBufferSizeCallBack);

    if (window == nullptr) {
        cout << "Creat GLFW WINDOW FAILED" << endl;
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "GLAD Get ProcAddress FAILED" << endl;
        glfwTerminate();
        return -1;
    }

    GLuint shaderProgramer = InitShader();

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramer);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glfwTerminate();
    return 0;
}