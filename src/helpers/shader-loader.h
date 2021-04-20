#pragma once
#include <string>

#include "./shader.cpp"

using namespace std;

class ShaderLoader {
    string prefix = "shaders/";

   private:
    inline bool fileExists(std::string name);
    int loadShaderFromFile(string filePath, int type);
    string loadFile(string filePath);

   public:
    ShaderLoader();
    Shader* load(string name);
    void use(int shaderProgram);
};

extern ShaderLoader shaderLoader;