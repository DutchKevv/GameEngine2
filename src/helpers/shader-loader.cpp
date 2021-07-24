#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include "./shader.cpp"

using namespace std;

class ShaderLoader
{

public:
    string basePath = "../shaders/";

    void use(int shaderProgram)
    {
        glUseProgram(shaderProgram);
    }

    Shader *load(string name)
    {
        string vertexSrc = loadFile(name + ".vs");
        string fragmentSrc = loadFile(name + ".fs");

        Shader *shader = new Shader(vertexSrc.c_str(), fragmentSrc.c_str());

        return shader;
    }

private:
    string prefix = "shaders/";

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

    string loadFile(string filePath)
    {
        filePath = prefix + filePath;

        bool f_exists = fileExists(filePath);

        std::ifstream t(filePath);
        std::string shaderString((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

        return shaderString;
    }
};