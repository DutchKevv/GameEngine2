#pragma once


#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
#include "./texture.h"
#include "./shader.cpp"
#include "logger.h"

using namespace std;

class ResourceManager
{
public:
	inline bool fileExists(std::string name);

	string loadFileToString(string filePath);

	Shader *loadShader(string name);

	Texture2D *loadTexture(std::string filePath, GLboolean alpha, std::string name, GLuint WRAP_S, GLuint WRAP_T);

	Texture2D *GetTexture(std::string name);

	void Clear();

	char *file_read(const char *filename);

	Shader loadShaderFromFile(string vShaderFile, string fShaderFile, const char *gShaderFile);
	// TODO - revert parameter (default false)
	Texture2D *loadTextureFromFile(std::string file, GLboolean alpha, GLuint WRAP_S, GLuint WRAP_T);
};
