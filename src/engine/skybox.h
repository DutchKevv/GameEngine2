#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "./shader.h"
#include "./renderObject.h"

class SkyBox : public RenderObject
{

public:
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint uniTransform;

	Shader *shader;

	GLuint VBO, VAO, texture;
	GLuint vertexColorLocation;
	GLuint vertexPosLocation;
	GLuint textureLocation;
	GLuint modelLoc;
	GLuint viewLoc;
	GLuint projLoc;

	GLuint cubemapTexture;

	void init();
	void draw(float delta);
	void renderScene(float delta, Shader *shader, bool isShadowRender);
	void move();
	void destroy();
};