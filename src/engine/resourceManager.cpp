#include "context.h"

#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./context.h"
#include <STB/stb_image.h>

#include "resourceManager.h"
#include "logger.h"

using namespace std;

// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(string vShaderFile, string fShaderFile, const char *gShaderFile, std::string name)
{
	// vShaderFile = context->paths->cwd + vShaderFile;
	// fShaderFile = context->paths->cwd + fShaderFile;

	if (Shaders.count(name) == 0)
	{
		Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	}

	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	Shader shader = Shaders[name];

	return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(std::string file, GLboolean alpha, std::string name, GLuint WRAP_S, GLuint WRAP_T)
{
	// file = context->paths->cwd + file;

	Textures[name] = loadTextureFromFile(file, alpha, WRAP_S, WRAP_T);
	return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

char *file_read(const char *filename)
{
	FILE *in = fopen(filename, "rb");
	if (in == NULL)
		return NULL;

	int res_size = BUFSIZ;
	char *res = (char *)malloc(res_size);
	int nb_read_total = 0;

	while (!feof(in) && !ferror(in))
	{
		if (nb_read_total + BUFSIZ > res_size)
		{
			if (res_size > 10 * 1024 * 1024)
				break;
			res_size = res_size * 2;
			res = (char *)realloc(res, res_size);
		}
		char *p_res = res + nb_read_total;
		nb_read_total += fread(p_res, 1, BUFSIZ, in);
	}

	fclose(in);
	res = (char *)realloc(res, nb_read_total + 1);
	res[nb_read_total] = '\0';
	return res;
}

Shader ResourceManager::loadShaderFromFile(string vShaderFile, string fShaderFile, const char *gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (vertexCode.empty())
		{
			consoleLog("ERROR::VERTEX::SHADER: Failed to read: " + vShaderFile);
		}

		if (vertexCode.empty())
		{
			consoleLog("ERROR::FRAGMENT::SHADER: Failed to read: " + fShaderFile);
		}

		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		consoleLog("ERROR::SHADER: Failed to read shader files");
	}

	// #ifdef GL_FRAGMENT_PRECISION_HIGH
	std::string precision = "\n precision highp float;\n\n";
	// #else
	// std::string precision = "\n precision mediump float;\n\n";
	// #endif

	fragmentCode.insert(17, precision);

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	const char *gShaderCode = geometryCode.c_str();

	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

// TODO - revert parameter (default false)
Texture2D ResourceManager::loadTextureFromFile(std::string file, GLboolean alpha, GLuint WRAP_S, GLuint WRAP_T)
{
	// enable reverting
	stbi_set_flip_vertically_on_load(true);

	// Create Texture object
	Texture2D texture;

	texture.Wrap_S = WRAP_S;
	texture.Wrap_T = WRAP_T;

	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height, nrChannels;
	unsigned char *image = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);

	if (!image)
	{
		consoleLog("Failed to load texture");
	}

	// Now generate texture
	texture.Generate(width, height, image);

	// free image data
	stbi_image_free(image);

	// disable reverting again
	stbi_set_flip_vertically_on_load(false);

	return texture;
}