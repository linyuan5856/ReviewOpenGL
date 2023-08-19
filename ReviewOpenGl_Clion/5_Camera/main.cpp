#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <cmath>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <direct.h>
#include <Shader.h>

#define  WIDTH 1024
#define  HEIGHT 768
using namespace std;
using namespace glm;

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

vec3 CameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 CameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 CameraUp = vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float lastTime;
float deltaTIme;
float lastX =0.0f;
float lasty = 0.0f;
float mpitch = 0.0f;
float myaw = -90.0f;

const char *containerTexPath = "../../Res/Texture/bg.jpg";
const char *specularMaskTexPath = "../../Res/Texture/containerTexPath.jpg";

const char *vShaderPath = "../../5_Camera/vs.shader";
const char *fShaderPath = "../../5_Camera/fs.shader";

void setBufferSizeCallBack(GLFWwindow *, int, int);

void processInput(GLFWwindow *window);

void setMouseCallBack(GLFWwindow *window, double x, double y);

void CheckShaderCompile(GLuint, string);


GLuint LoadTexture(const char *texturePath);

void setBufferSizeCallBack(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    float currentTime = (float) glfwGetTime();
    deltaTIme = currentTime - lastTime;
    lastTime = currentTime;
    float speed = deltaTIme * 2.0f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        CameraPos += CameraFront * speed;
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        CameraPos -= CameraFront * speed;
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        CameraPos -= glm::normalize(glm::cross(CameraFront, CameraUp)) * speed;
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        CameraPos += glm::normalize(glm::cross(CameraFront, CameraUp)) * speed;
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

void setMouseCallBack(GLFWwindow *window, double x, double y) {
    if(firstMouse){
        lastX=x;
        lasty=y;
        firstMouse= false;
    }
    float deltaX = (float) (x - lastX);
    float deltaY = (float) (lasty - y);

    lastX = x;
    lasty = y;

    float sensitivity = 0.25f;
    deltaX *= sensitivity;
    deltaY *= sensitivity;

    myaw += deltaX;
    mpitch += deltaY;
    if(mpitch>89)
        mpitch=89;
    if(mpitch<-89)
        mpitch=-89;

    float dirX = cos(glm::radians(myaw)) * cos(glm::radians(mpitch));
    float dirY = sin(glm::radians(mpitch));
    float dirZ = sin(glm::radians(myaw)) * cos(glm::radians(mpitch));
    glm::vec3 direction = vec3(dirX, dirY, dirZ);
    CameraFront = glm::normalize(direction);
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
    glfwSetCursorPosCallback(window, setMouseCallBack);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    Shader myShader = Shader(vShaderPath, fShaderPath);
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint texture1 = LoadTexture(containerTexPath);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
        glm::mat4 project = glm::mat4(1.0f);
        project = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);
        myShader.setMat4("V", view);
        myShader.setMat4("P", project);

        for (int i = 0; i < 10; ++i) {
            float angle = i * 20.0f + 5.0f;
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            myShader.setMat4("M", model);


            glBindVertexArray(VAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}