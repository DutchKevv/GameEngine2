#pragma once
#include <glm/glm.hpp>
#include "shader.cpp"
#include "camera.h"
#include "renderObject.h"

class SkyBox : public RenderObject
{

public:
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint uniTransform;

	Shader *shader;

	unsigned int VBO, VAO, texture;
	unsigned int vertexColorLocation;
	unsigned int vertexPosLocation;
	unsigned int textureLocation;
	unsigned int modelLoc;
	unsigned int viewLoc;
	unsigned int projLoc;

	unsigned int cubemapTexture;

	// SkyBox();

	void init();
	void draw(float delta);
	void renderScene(float delta, Shader *shader, bool isShadowRender);
	void move();
	void destroy();
};