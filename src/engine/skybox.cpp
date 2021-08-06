// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./context.h"
// #include <STB/stb_image.h>
#include "skybox.h"
#include "shader.cpp"
// #include "resourceManager.cpp"

using namespace std;
using namespace glm;

unsigned int loadCubemap(vector<std::string> faces);

static float skyboxVertices[] = {
	// positions
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f};


void SkyBox::init()
{

	// shader
	Shader *shader = context->resourceManager->loadShader("skybox");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

	// load textures
	// -------------
	// vector<std::string> faces{

	// 	"textures/skybox/elbrus/elbrus_rt.jpg",
	// 	"textures/skybox/elbrus/elbrus_lf.jpg",
	// 	"textures/skybox/elbrus/elbrus_up.jpg",
	// 	"textures/skybox/elbrus/elbrus_dn.jpg",
	// 	"textures/skybox/elbrus/elbrus_bk.jpg",
	// 	"textures/skybox/elbrus/elbrus_ft.jpg"};

	// vector<std::string> faces{

	// 	"textures/skybox/3/right.jpg",
	// 	"textures/skybox/3/left.jpg",
	// 	"textures/skybox/3/top.jpg",
	// 	"textures/skybox/3/bottom.jpg",
	// 	"textures/skybox/3/back.jpg",
	// 	"textures/skybox/3/front.jpg"};

	// vector<std::string> faces{
	// 	"textures/skybox/mandaris/mandaris_rt.tga",
	// 	"textures/skybox/mandaris/mandaris_lf.tga",
	// 	"textures/skybox/mandaris/mandaris_up.tga",
	// 	"textures/skybox/mandaris/mandaris_dn.tga",
	// 	"textures/skybox/mandaris/mandaris_bk.tga",
	// 	"textures/skybox/mandaris/mandaris_ft.tga"};

	vector<std::string> faces{
		"textures/skybox/jajlands1/jajlands1_rt.jpg",
		"textures/skybox/jajlands1/jajlands1_lf.jpg",
		"textures/skybox/jajlands1/jajlands1_up.jpg",
		"textures/skybox/jajlands1/jajlands1_dn.jpg",
		"textures/skybox/jajlands1/jajlands1_bk.jpg",
		"textures/skybox/jajlands1/jajlands1_ft.jpg"};

	cubemapTexture = loadCubemap(faces);
};

void SkyBox::draw(float delta){

};

void SkyBox::renderScene(float delta, Shader *shader, bool isShadowRender)
{
	// std::cout << "Render skybox: " << std::endl;

	Shader *skyBoxShader = context->resourceManager->loadShader("skybox");
	skyBoxShader->use();

	//    glm::mat4 model;
	//    glm::mat4 view = context->camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(scene->camera->Zoom, (float)context->windowW / (float)context->windowH, 0.1f, 1.0f);
	////    shader->setMat4("model", model);
	//    shader->setMat4("view", view);
	//    shader->setMat4("projection", projection);
	//    shader->setVec3("cameraPos", context->camera->Position);

	// draw skybox as last
	glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
	// glDepthMask(GL_FALSE);

	glm::mat4 view = glm::mat4(glm::mat3(scene->camera->GetViewMatrix())); // remove translation from the view matrix
	skyBoxShader->setMat4("view", view);
	skyBoxShader->setMat4("projection", projection);

	// skybox cube
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
						  // glDepthMask(GL_TRUE);
}

void SkyBox::destroy()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
};

unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(false);
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	stbi_set_flip_vertically_on_load(true);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}