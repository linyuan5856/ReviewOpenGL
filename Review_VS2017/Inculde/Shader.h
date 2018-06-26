#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/detail/type_vec2.hpp>
#include <glm/mat2x3.hpp>


using namespace std;

class Shader
{
public:
	// ����ID
	unsigned int ID;

	// ��������ȡ��������ɫ��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const char* geometryPath = nullptr);
	// ʹ��/�������
	void use();
	// uniform���ߺ���
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setFloat(const string &name, float value) const;

	void setVec2(const string &name, const glm::vec2 &value) const;
	
	void setVec2(const string &name, float x, float y) const;
	
	void setVec3(const string &name, const glm::vec3 &value) const;
	
	void setVec3(const string &name, float x, float y, float z) const;
	
	void setVec4(const string &name, const glm::vec4 &value) const;
	
	void setVec4(const string &name, float x, float y, float z, float w);
	
	void setMat2(const string &name, const glm::mat2 &mat) const;
	
	void setMat3(const string &name, const glm::mat3 &mat) const;
	
	void setMat4(const string &name, const glm::mat4 &mat) const;
	

private:
	void checkCompileErrors(unsigned int, string);
};
#endif