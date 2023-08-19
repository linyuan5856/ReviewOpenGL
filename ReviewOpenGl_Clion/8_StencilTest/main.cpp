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
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
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

glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
};

vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);

vec3 CameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 CameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 CameraUp = vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float lastTime;
float deltaTIme;
float lastX = 0.0f;
float lasty = 0.0f;
float mpitch = 0.0f;
float myaw = -90.0f;

const char *containerTexPath = "../../Res/Texture/container2.png";
const char *specularMaskTexPath = "../../Res/Texture/container2_specular.png";

const char *vShaderPath = "../../8_StencilTest/vs.shader";
const char *fShaderPath = "../../8_StencilTest/fs.shader";

const char *LampVShaderPath = "../../8_StencilTest/lampvs.shader";
const char *LampFShaderPath = "../../8_StencilTest/lampfs.shader";

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
    if (firstMouse) {
        lastX = x;
        lasty = y;
        firstMouse = false;
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
    if (mpitch > 89)
        mpitch = 89;
    if (mpitch < -89)
        mpitch = -89;

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
    Shader lampShader = Shader(LampVShaderPath, LampFShaderPath);
    GLuint VAO, VBO, LampVAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &LampVAO);
    glBindVertexArray(LampVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    GLuint contaninerTex = LoadTexture(containerTexPath);
    GLuint specularMaskTex = LoadTexture(specularMaskTexPath);
    myShader.use();
    myShader.setInt("material.diffuse", 0);
    myShader.setInt("material.specular", 1);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();

        myShader.setVec3("viewPos", CameraPos);
        myShader.setFloat("material.shininess", 64.0f);

        // directional light
        myShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        myShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        myShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        myShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        myShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        myShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        myShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        myShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        myShader.setFloat("pointLights[0].constant", 1.0f);
        myShader.setFloat("pointLights[0].linear", 0.09);
        myShader.setFloat("pointLights[0].quadratic", 0.032);
        // point light 2
        myShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        myShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        myShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        myShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        myShader.setFloat("pointLights[1].constant", 1.0f);
        myShader.setFloat("pointLights[1].linear", 0.09);
        myShader.setFloat("pointLights[1].quadratic", 0.032);
        // point light 3
        myShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        myShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        myShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        myShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        myShader.setFloat("pointLights[2].constant", 1.0f);
        myShader.setFloat("pointLights[2].linear", 0.09);
        myShader.setFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        myShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        myShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        myShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        myShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        myShader.setFloat("pointLights[3].constant", 1.0f);
        myShader.setFloat("pointLights[3].linear", 0.09);
        myShader.setFloat("pointLights[3].quadratic", 0.032);
        // spotLight
        myShader.setVec3("spotLight.position", CameraPos);
        myShader.setVec3("spotLight.direction", CameraFront);
        myShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        myShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        myShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        myShader.setFloat("spotLight.constant", 1.0f);
        myShader.setFloat("spotLight.linear", 0.09);
        myShader.setFloat("spotLight.quadratic", 0.032);
        myShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        myShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
        glm::mat4 project = glm::mat4(1.0f);
        project = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);
        myShader.setMat4("V", view);
        myShader.setMat4("P", project);

        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, contaninerTex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMaskTex);
        for (int i = 0; i < 10; ++i) {
            float angle = i * 20.0f + 5.0f;
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            myShader.setMat4("M", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        lampShader.use();
        lampShader.setMat4("P", project);
        lampShader.setMat4("V", view);
        glBindVertexArray(LampVAO);

        for (unsigned int i = 0; i < 4; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.1f));
            lampShader.setMat4("M", model);
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