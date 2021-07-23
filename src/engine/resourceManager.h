#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "texture.h"
#include "../helpers/shader.cpp"

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined.
class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;
	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader LoadShader(std::string vShaderFile, std::string fShaderFile, const char *gShaderFile, std::string name);
	// Retrieves a stored sader
	static Shader GetShader(std::string name);
	// Loads (and generates) a texture from file
	static Texture2D LoadTexture(std::string file, GLboolean alpha, std::string name, GLuint WRAP_S = GL_REPEAT, GLuint WRAP_T = GL_REPEAT);
	// Retrieves a stored texture
	static Texture2D GetTexture(std::string name);
	// Properly de-allocates all loaded resources
	static void Clear();

private:
	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ResourceManager() {}
	// Loads and generates a shader from file
	static Shader loadShaderFromFile(std::string vShaderFile, std::string fShaderFile, const char *gShaderFile = nullptr);
	// Loads a single texture from file
	static Texture2D loadTextureFromFile(std::string file, GLboolean alpha, GLuint WRAP_S, GLuint WRAP_T);
};

#endif