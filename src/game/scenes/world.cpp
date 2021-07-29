#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../engine/scene.cpp"
#include "../../engine/camera.h"
#include "../../engine/context.h"
#include "../../engine/skybox.cpp"
#include "../../engine/texture.h"
#include "../../engine/model.cpp"
#include "../../engine/shader.cpp"
#include "../../shape/cube.cpp"
#include "../../shape/plane.cpp"
#include "../../lights/spotlight.cpp"

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

class WorldScene : public Scene
{
public:
	ShapeCube *cube1;
	ShapeCube *cube2;
	ShapeCube *cube3;
	ShapeCube *cube4;
	ShapeCube *cube5;
	Spotlight *spotlight;
	ShapePlane *floor;
	SkyBox *skybox;

	unsigned int depthMapFBO;
	unsigned int depthMap;
	unsigned int depthCubemap;

	Shader *shader;
	Shader *depthShader;
	Texture2D texture;
	Model *test;

	void init()
	{
		shader = context->resourceManager->loadShader("shadow");
		depthShader = context->resourceManager->loadShader("shadow_depth");
		texture = context->resourceManager->loadTexture("container2.jpg", true, "wall", 0, 0);

		// configure depth map FBO
		// -----------------------

		// shadow buffer
		glGenFramebuffers(1, &depthMapFBO);

		// glGenTextures(1, &depthCubemap);

		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = {1.0, 1.0, 1.0, 1.0};
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// shader configuration
		// --------------------
		shader->use();
		shader->setInt("diffuseTexture", 0);
		shader->setInt("shadowMap", 1);

		std::cout << "init world \n";

		cube1 = new ShapeCube();
		cube2 = new ShapeCube();
		cube3 = new ShapeCube();
		cube4 = new ShapeCube();
		cube5 = new ShapeCube();
		spotlight = new Spotlight();
		floor = new ShapePlane();
		skybox = new SkyBox();

		// load models
		// -----------
		test = new Model("game/models/trees/sdf/tree.fbx");
		// test = new Model("game/models/trees/cartoon/CartoonTree.fbx");
		// test = new Model("game/models/tree-low-poly/lowpolytree.obj");
		// test = new Model("game/models/plane/FREOBJ.obj");

		camera = new Camera(glm::vec3(0.0f, 10.0f, 20.0f));

		cube1->position = glm::vec3(0.0f, 1.5f, 0.0);
		cube2->position = glm::vec3(2.0f, 0.0f, -15.0f);
		cube3->position = glm::vec3(-1.5f, 0.0f, -2.5f);
		cube4->position = glm::vec3(-3.8f, 0.0f, -12.3f);
		cube5->position = glm::vec3(0.0f, 0.0f, 0.0f);

		addChild(skybox, this);
		addChild(cube1, this);
		addChild(cube2, this);
		addChild(cube3, this);
		addChild(cube4, this);
		addChild(cube5, this);
		addChild(spotlight, this);
		addChild(floor, this);
		addChild(test, this);
	}

	void draw(float delta)
	{
		// 1. render depth of scene to texture (from light's perspective)
		// --------------------------------------------------------------

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		float near_plane = 1.0f, far_plane = 75.5f;
		BaseObject *spotlight = getChildByClass<Spotlight>();
		// glm::vec3 lightPos(-0.0f, 40.0f, -100.0f);
		// lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		// lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightView = glm::lookAt(spotlight->position, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
		// render scene from light's point of view
		depthShader->use();
		depthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.ID);
		renderScene(delta, depthShader, true);
		glBindFramebuffer(GL_FRAMEBUFFER, context->engine->fbo);

		// reset viewport
		glViewport(0, 0, context->display->windowW, context->display->windowH);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 2. render scene as normal using the generated depth/shadow map
		// --------------------------------------------------------------
		glViewport(0, 0, context->display->windowW, context->display->windowH);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->use();
		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)context->display->windowW / (float)context->display->windowH, 0.1f, 100.0f);
		glm::mat4 view = camera->GetViewMatrix();

		shader->setMat4("projection", projection);
		shader->setMat4("view", view);

		// set light uniforms
		shader->setVec3("viewPos", camera->Position);
		// shader->setVec3("lightPos", lightPos);
		shader->setVec3("lightPos", spotlight->position);
		shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.ID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		renderScene(delta, shader, false);
	}

	// renders the 3D scene
	// --------------------
	void renderScene(float delta, Shader *shader, bool isShadowRender)
	{
		// std::cout << "render world scene \n";
		glEnable(GL_DEPTH_TEST);
		Scene::renderScene(delta, shader, isShadowRender);
		glDisable(GL_DEPTH_TEST);
	}
};