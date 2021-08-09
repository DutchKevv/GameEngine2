#pragma once

#include <string>
#include "./texture.h"
#include "./shader.cpp"

class ResourceManager
{
public:
	inline bool fileExists(std::string name);

	std::string loadFileToString(std::string filePath);

	Shader *loadShader(std::string name);

	Texture2D *loadTexture(std::string filePath, GLboolean alpha, std::string name, GLuint WRAP_S, GLuint WRAP_T);

	Texture2D *GetTexture(std::string name);

	void Clear();

	char *file_read(const char *filename);

	Shader loadShaderFromFile(std::string vShaderFile, std::string fShaderFile, const char *gShaderFile);
	// TODO - revert parameter (default false)
	Texture2D *loadTextureFromFile(std::string file, GLboolean alpha, GLuint WRAP_S, GLuint WRAP_T);
};
