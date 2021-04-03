#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>

using namespace std;

class ShaderLoader {
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;

   public:
    unsigned int load(std::string vertexPath, std::string fragmentPath) {
        bool f_exists = fileExists(fragmentPath);
        bool v_exists = fileExists(vertexPath);

        ifstream v(vertexPath);  //taking file as inputstream
        string v_str;
        if (v) {
            ostringstream ss;
            ss << v.rdbuf();  // reading data
            v_str = ss.str();
        }

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char *vertexString = v_str.c_str();
        glShaderSource(vertexShader, 1, &vertexString, NULL);
        glCompileShader(vertexShader);

        ifstream f(fragmentPath);  //taking file as inputstream
        string f_str;
        if (f) {
            ostringstream ss;
            ss << f.rdbuf();  // reading data
            f_str = ss.str();
        }

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char *fragmentString = f_str.c_str();
        glShaderSource(fragmentShader, 1, &fragmentString, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        // not needed after linking
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }

   private:
    string prefix = "shaders/";

    inline bool fileExists(std::string name) {
        name = prefix + name;

        std::cout << ("checking : '" + name + "'") << std::endl;
        ifstream ifile;
        ifile.open(name);
        if (ifile) {
            cout << "file exists";
            return true;
        } else {
            cout << "file doesn't exist";
            return false;
        }
    }
};