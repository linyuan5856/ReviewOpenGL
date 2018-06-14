#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <cmath>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <direct.h>

#define  WIDTH 800
#define  HEIGHT 600
using namespace std;
using namespace glm;

//region pos and UV
float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};
//endregion

GLuint indexs[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
};

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

const char *vertexShaderSource = R"(
#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec2 aUv;

out vec2 uv;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main(){
gl_Position=P*V*M*vec4(aPos,1.0);
uv=aUv;
}
)";
const char *fragShaderSource = R"(
#version 330 core
out vec4 finalColor;
in vec2 uv;

uniform sampler2D tex1;
uniform sampler2D tex2;
//uniform vec4 myColor;

void main(){
 finalColor=texture(tex1,uv);
//*texture(tex2,uv);
//*myColor;
}
)";

const char *texPath1 = "E:/ReviewOpenGL//ReviewOpenGl/Res/Texture/bg.jpg";
const char *texPath2 = "E:/ReviewOpenGL//ReviewOpenGl/Res/Texture/container.jpg";

void setBufferSizeCallBack(GLFWwindow *, int, int);

void processInput(GLFWwindow *window);

void CheckShaderCompile(GLuint, string);

GLuint LoadShader(const char *vShaderSource, const char *fShaderSource);

GLuint LoadTexture(const char *texturePath);


void setBufferSizeCallBack(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

GLuint LoadShader(const char *vShaderSource, const char *fShaderSource) {

    GLuint vShader, fShader, programer;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSource, nullptr);
    glCompileShader(vShader);
    CheckShaderCompile(vShader, "VERTEX");

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderSource, nullptr);
    glCompileShader(fShader);
    CheckShaderCompile(fShader, "FRAG");

    programer = glCreateProgram();
    glAttachShader(programer, vShader);
    glAttachShader(programer, fShader);
    glLinkProgram(programer);
    CheckShaderCompile(programer, "PROGRAMMER");
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return programer;
}

void CheckShaderCompile(GLuint shader, string ShaderType) {
    GLint succes;
    char info[512];

    if (ShaderType == "PROGRAMMER") {

        glGetProgramiv(shader, GL_LINK_STATUS, &succes);
        if (!succes) {
            glGetProgramInfoLog(shader, 512, nullptr, info);
            cout << "PROGRAM LINK ERROR->   " << info << endl;
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
        if (!succes) {
            glGetShaderInfoLog(shader, 512, nullptr, info);
            cout << ShaderType << "COMPILE ERROR->  " << info << endl;
        }
    }
}

GLuint LoadTexture(const char *texturePath) {
    GLint width, height, channel;
    stbi_set_flip_vertically_on_load(1);
    GLubyte *data = stbi_load(texturePath, &width, &height, &channel, 0);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data != nullptr) {
        if (channel == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    } else {
        cout << "Path->" << texturePath << "||  Load Image Wrong-->   " << stbi_failure_reason() << endl;
    }
    stbi_image_free(data);
    return texture;
}


int main() {
    int res = glfwInit();
    if (res == GLFW_FALSE) {
        glfwTerminate();
        return -1;
    }
    // cout << glfwGetVersionString() << endl;
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
    glEnable(GL_DEPTH_TEST);

    GLuint shaderProgram = LoadShader(vertexShaderSource, fragShaderSource);
    GLuint VAO, VBO;//, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs), indexs, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint texture1 = LoadTexture(texPath1);
    GLuint texture2 = LoadTexture(texPath2);
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "tex1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "tex2"), 1);


    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        // float blue = sin(glfwGetTime()) / 2.0f + 0.5f;
        // glUniform4f(glGetUniformLocation(shaderProgram, "myColor"), 0.0f, 0.0f, blue, 1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 project = glm::mat4(1.0f);
        project = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "V"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "P"), 1, GL_FALSE, glm::value_ptr(project));
        for (int i = 0; i < 10; ++i) {
            float angle = i * 20.0f + 5.0f;
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(model));

            glBindVertexArray(VAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}