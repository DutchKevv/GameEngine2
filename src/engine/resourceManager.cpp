#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "stb_image/stb_image.h"
#include "./texture.h"
#include "./shader.cpp"

// #include "resourceManager.h"
#include "logger.cpp"

using namespace std;

const string prefixShader = "shaders/";
const string prefixTextures = "textures/";

map<std::string, Texture2D> Textures;
map<std::string, Shader *> Shaders;

class ResourceManager
{
public:
	inline bool fileExists(std::string name)
	{
		std::cout << ("checking : '" + name) << std::endl;
		ifstream ifile;
		ifile.open(name);
		if (!ifile)
		{
			cout << ("cannot find : '" + name + "'\n");
			return false;
		}

		return true;
	}

	string loadFileToString(string filePath)
	{
		filePath = prefixShader + filePath;

		bool f_exists = fileExists(filePath);

		std::ifstream t(filePath);
		std::string shaderString((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

		return shaderString;
	}

	Shader *loadShader(string name)
	{
		if (Shaders.count(name) == 0)
		{
			string vertexSrc = loadFileToString(name + ".vs");
			string fragmentSrc = loadFileToString(name + ".fs");

			Shaders[name] = new Shader(vertexSrc.c_str(), fragmentSrc.c_str());
		}

		return Shaders[name];
	}

	Texture2D loadTexture(std::string filePath, GLboolean alpha, std::string name, GLuint WRAP_S, GLuint WRAP_T)
	{
		filePath = prefixTextures + filePath;
		Textures[name] = loadTextureFromFile(filePath, alpha, WRAP_S, WRAP_T);
		return Textures[name];
	}

	Texture2D GetTexture(std::string name)
	{
		return Textures[name];
	}

	void Clear()
	{
		// // (Properly) delete all shaders
		// for (auto iter : Shaders)
		// 	glDeleteProgram(iter.second.ID);
		// // (Properly) delete all textures
		// for (auto iter : Textures)
		// 	glDeleteTextures(1, &iter.second.ID);
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

	Shader loadShaderFromFile(string vShaderFile, string fShaderFile, const char *gShaderFile)
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
		// Shader shader;
		// shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
		return Shader(vShaderCode, fShaderCode);
	}

	// TODO - revert parameter (default false)
	Texture2D loadTextureFromFile(std::string file, GLboolean alpha, GLuint WRAP_S, GLuint WRAP_T)
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
			std::cout << "Failed to load texture \n";
		}

		// Now generate texture
		texture.Generate(width, height, image);

		// free image data
		stbi_image_free(image);

		// disable reverting again
		stbi_set_flip_vertically_on_load(false);

		return texture;
	}
};
