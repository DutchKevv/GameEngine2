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

class ShaderLoader {

   public:
    void use(int shaderProgram) {
        glUseProgram(shaderProgram);
    }

    Shader* load(string name) {
        string vertexSrc = loadFile(name + ".vs");
        string fragmentSrc = loadFile(name + ".fs");
        Shader* shader(vertexSrc.c_str(), fragmentSrc.c_str());
        // unsigned int shaderProgram = glCreateProgram();
        // unsigned int vertexShader = this->loadShaderFromFile(name + ".vs", GL_VERTEX_SHADER);
        // unsigned int fragmentShader = this->loadShaderFromFile(name + ".fs", GL_FRAGMENT_SHADER);

        // glAttachShader(shaderProgram, vertexShader);
        // glAttachShader(shaderProgram, fragmentShader);
        // glLinkProgram(shaderProgram);
        // glUseProgram(shaderProgram);

        // int success;
        // char infoLog[512];

        // glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        // if (!success) {
        //     glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        //     cout << "ERROR::SHADER-PROGRAM::COMPILATION_FAILED\n"
        //          << infoLog << std::endl;
        // }

        // // not needed after linking
        // glDeleteShader(vertexShader);
        // glDeleteShader(fragmentShader);

        return shader;
    }

   private:
    string prefix = "shaders/";

    inline bool fileExists(std::string name) {
        std::cout << ("checking : '" + name + "'\n") << std::endl;
        ifstream ifile;
        ifile.open(name);
        if (ifile) {
            cout << "file exists\n";
            return true;
        } else {
            cout << "file doesn't exist\n";
            return false;
        }
    }

    int loadShaderFromFile(string filePath, int type) {
        filePath = prefix + filePath;

        bool f_exists = fileExists(filePath);
        int success;
        int shader;
        char infoLog[512];

        ifstream v(filePath);  //taking file as inputstream
        string v_str;
        if (v) {
            ostringstream ss;
            ss << v.rdbuf();  // reading data
            v_str = ss.str();
        }

        shader = glCreateShader(type);

        const char *shaderString = v_str.c_str();
        glShaderSource(shader, 1, &shaderString, NULL);
        glCompileShader(shader);

        // print compile errors if any
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                 << infoLog << std::endl;
        }

        return shader;
    }

    string loadFile(string filePath) {
        filePath = prefix + filePath;

        bool f_exists = fileExists(filePath);
        int success;
        int shader;
        char infoLog[512];

        ifstream v(filePath);  //taking file as inputstream
        string v_str;
        if (v) {
            ostringstream ss;
            ss << v.rdbuf();  // reading data
            v_str = ss.str();
        }

        const char *shaderString = v_str.c_str();

        return shaderString;
    }
};