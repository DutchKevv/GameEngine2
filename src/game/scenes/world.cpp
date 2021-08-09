#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./world.h"
#include "../../engine/camera.h"
#include "../../engine/engine.h"
#include "../../engine/context.h"

const unsigned int SHADOW_WIDTH = 10240, SHADOW_HEIGHT = 10240;
vector<glm::vec4> treePositions;
const unsigned int space = 330;
const unsigned int trees = 300;
const unsigned int trees2 = 399;
const unsigned int trees3 = 399;
const unsigned int rocks = 75;

void WorldScene::init()
{
	shader = context->resourceManager->loadShader("shadow");
	depthShader = context->resourceManager->loadShader("shadow_depth");

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

	skybox = new SkyBox();
	spotlight = new Spotlight();
	cube1 = new ShapeCube();
	cube2 = new ShapeCube();
	cube3 = new ShapeCube();
	// cube4 = new ShapeCube();
	// cube5 = new ShapeCube();
	floor = new ShapePlane();
	// heightMap = new HeightMap();

	camera = new Camera(glm::vec3(0.0f, 4.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), -75.5f);

	// load models
	// -----------

	// player
	player = new Model("game/models/player/vampire/vampire.dae");
	danceAnimation = new Animation("game/models/player/vampire/vampire.dae", player);
	animator = new Animator(danceAnimation);
	animator->PlayAnimation(danceAnimation);

	// player = new Model("game/models/player/player.obj", 1);
	player->position = glm::vec3(0.0f, 0.0f, 0.0f);
	// player->scale = glm::vec3(0.01f);

	// test = new Model("game/models/trees/cartoon/CartoonTree.fbx");
	// treeModel2 = new Model("game/models/cube/cube.obj", 1);
	treeModel = new Model("game/models/tree-low-poly/polytree1.obj", 10000);
	treeModel3 = new Model("game/models/tree-low-poly/polytree4.obj", 10000);
	// treeModel2 = new Model("game/models/tree-low-poly/pinetree2withrocks.obj", 10000);
	treeModel2 = new Model("game/models/tree-low-poly/pinetree2.obj", 10009);
	sun = new Model("game/models/sphere/sphere.obj", 1);
	castle = new Model("game/models/castle/tower/medieval_tower_2.obj", 1);

	// treeModel2 = new Model("game/models/tree-low-poly/polytree1.obj", 10000);
	// treeModel2 = new Model("game/models/plane/FREOBJ.obj", 2);
	// rockModel = new Model("game/models/stone/stone.obj");
	// treeModel = new Model("game/models/tree-low-poly/lowpolytree.obj");
	// treeModel = new Model("game/models/tree-low-poly/polytree1.obj");

	cube1->position = glm::vec3(10.0f, 21.5f, 40.0);
	cube2->position = glm::vec3(2.0f, 20.0f, -15.0f);
	cube3->position = glm::vec3(-1.5f, 20.0f, -2.5f);
	// cube4->position = glm::vec3(-3.8f, 0.0f, -12.3f);
	// cube5->position = glm::vec3(0.0f, 0.0f, 0.0f);
	// test->position = glm::vec3(1.0f, 2.0f, 0.0f);

	addChild(spotlight, this);
	// addChild(skybox, this);
	// addChild(sun, this);
	addChild(floor, this);
	addChild(treeModel2, this);
	addChild(treeModel, this);

	addChild(castle, this); 
	addChild(player, this);
	// addChild(cube1, this);
	// addChild(cube2, this);
	// addChild(cube3, this);
	// addChild(test, this);
	// addChild(cube4, this);
	// addChild(cube5, this);

	// addChild(heightMap, this);

	float halfSpace = space / 2;
	for (int i = 0; i < trees; i++)
	{
		treePositions.push_back(
			glm::vec4((rand() % space) - halfSpace, 0.0f, (rand() % space) - halfSpace, rand() % 100));
	}

	for (int i = 0; i < trees2; i++)
	{
		treePositions2.push_back(
			glm::vec4((rand() % space) - halfSpace, 0.0f, (rand() % space) - halfSpace, rand() % 100));
	}

	for (int i = 0; i < rocks; i++)
	{
		rockPositions.push_back(
			glm::vec4((rand() % space) - halfSpace, 0.0f, (rand() % space) - halfSpace, rand() % 100));
	}

	// // load random positions for models
	// for (int i = 0; i < trees; i++)
	// {
	// 	// Model *model = new Model("game/models/tree-low-poly/lowpolytree.obj");
	// 	glm::vec4 random = glm::vec4((rand() % space) - halfSpace, 1.8f, (rand() % space) - halfSpace, rand() % 100);
	// 	tree->scale = glm::vec3(random.w);
	// 	tree->position = random;

	// 	addChild(tree, this);
	// }

	// for (int i = 0; i < rocks; i++)
	// {
	// 	Model *model = new Model("game/models/stone/stone.obj");
	// 	glm::vec4 random = glm::vec4((rand() % space) - halfSpace, -1.0f, (rand() % space) - halfSpace, rand() % 100);
	// 	model->scale = glm::vec3(random.w / 10);
	// 	model->position = random;

	// 	addChild(model, this);
	// }
}

void WorldScene::draw(float delta)
{
	// 1. render depth of scene to texture (from light's perspective)
	// --------------------------------------------------------------
	// shader->setBool("useTexture", true);
	animator->UpdateAnimation(delta);
	// render
	// ------
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 0.0f, far_plane = 75.5f;

	// lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
	lightProjection = glm::ortho(-80.0f, 80.0f, -80.0f, 80.0f, near_plane, far_plane);
	// lightProjection = glm::ortho(-680.0f, 680.0f, -680.0f, 680.0f, near_plane, far_plane);
	
	// lightView = glm::lookAt(glm::vec3(-0.0f, 40.0f, -30.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightView = glm::lookAt(spotlight->position, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
	
	lightSpaceMatrix = lightProjection * lightView;
	
	// render scene from light's point of view
	depthShader->use();
	depthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	// render with GL_CULL_FACE to fix 'peter panning' in the shadow
	// https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	renderScene(delta, depthShader, true);
	// glCullFace(GL_BACK); // don't forget to reset original culling face
	glDisable(GL_CULL_FACE);


	glBindFramebuffer(GL_FRAMEBUFFER, context->engine->fbo);

	// reset viewport
	glViewport(0, 0, context->display->windowW, context->display->windowH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 2. render scene as normal using the generated depth/shadow map
	// --------------------------------------------------------------
	glViewport(0, 0, context->display->windowW, context->display->windowH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->use();

	// draw distance
	// TODO - does not set float correct in display class
	float ratio = (float)context->display->windowW / (float)context->display->windowH;
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), ratio, 1.1f, 10000.0f);

	glm::mat4 view = camera->GetViewMatrix();

	shader->setMat4("projection", projection);
	shader->setMat4("view", view);

	// set light uniforms
	shader->setVec3("viewPos", camera->Position);
	shader->setVec3("light.position", spotlight->position);
	shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	renderScene(delta, shader, false);
}

// renders the 3D scene
// --------------------
void WorldScene::renderScene(float delta, Shader *shader, bool isShadowRender)
{
	// std::cout << "render world scene \n";
	glEnable(GL_DEPTH_TEST);
	// camera->followObject(player);
	sun->position = glm::vec3(spotlight->position.x, spotlight->position.y - 2.0f, spotlight->position.z - 10.0f);
	shader->use();

	auto transforms = animator->GetPoseTransforms();
	for (int i = 0; i < transforms.size(); ++i) {
		shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
	}

	Scene::renderScene(delta, shader, isShadowRender);

	// for (unsigned int i = 0; i < trees; i++)
	// {
	// 	glm::mat4 model = glm::mat4(1.0f);
	// 	glm::vec4 random = treePositions[i];

	// 	model = glm::scale(model, glm::vec3(3.0f));
	// 	model = glm::translate(model, glm::vec3(random.x, 0.0f, random.z));
	// 	model = glm::rotate(model, random.w, glm::vec3(0.0f, 1.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)
	// 	model = glm::rotate(model, random.w / 200, glm::vec3(1.0f, 0.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)
	// 	// treeModel->position = glm::vec3(random);
	// 	shader->setMat4("model", model);
	// 	// // textureGrass.Bind();
	// 	treeModel2->renderScene(delta, shader, isShadowRender);
	// }

	// for (unsigned int i = 0; i < trees2; i++)
	// {
	// 	glm::mat4 model = glm::mat4(1.0f);
	// 	glm::vec4 random = treePositions2[i];

	// 	model = glm::scale(model, glm::vec3(3.0f));
	// 	model = glm::translate(model, glm::vec3(random.x, 0.0f, random.z));
	// 	model = glm::rotate(model, random.w, glm::vec3(0.0f, 1.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)
	// 	model = glm::rotate(model, random.w / 200, glm::vec3(1.0f, 0.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)
	// 	// treeModel->position = glm::vec3(random);
	// 	shader->setMat4("model", model);
	// 	// // textureGrass.Bind();
	// 	treeModel->renderScene(delta, shader, isShadowRender);
	// }

	// for (unsigned int i = 0; i < trees3; i++)
	// {
	// 	glm::mat4 model = glm::mat4(1.0f);
	// 	glm::vec4 random = treePositions[i];

	// 	model = glm::scale(model, glm::vec3(3.0f));
	// 	model = glm::translate(model, glm::vec3(random.x, 1.9f, random.z));
	// 	// treeModel->position = glm::vec3(random);
	// 	shader->setMat4("model", model);
	// 	// // textureGrass.Bind();
	// 	treeModel3->renderScene(delta, shader, isShadowRender);
	// }

	// for (unsigned int i = 0; i < rocks; i++)
	// {
	// 	glm::mat4 model = glm::mat4(1.0f);
	// 	glm::vec4 random = rockPositions[i];

	// 	model = glm::scale(model, glm::vec3(1.0f));
	// 	model = glm::translate(model, glm::vec3(random.x, 0.0f, random.z));
	// 	// treeModel->position = glm::vec3(random);
	// 	shader->setMat4("model", model);
	// 	// // textureGrass.Bind();
	// 	rockModel->renderScene(delta, shader, isShadowRender);
	// }

	// for (unsigned int i = 0; i < rockPositions.size(); i++)
	// {
	// 	glm::mat4 model = glm::mat4(1.0f);
	// 	glm::vec4 random = rockPositions[i];

	// 	model = glm::translate(model, glm::vec3(random.x, 0.0f, random.z));
	// 	model = glm::scale(model, glm::vec3(random.w / 25));
	// 	// // model = glm::scale(model, glm::vec3(random.w / 100));
	// 	// treeModel->position = glm::vec3(random);
	// 	shader->setMat4("model", model);
	// 	// // textureGrass.Bind();
	// 	rockModel->renderScene(delta, shader, isShadowRender);
	// }

	glDisable(GL_DEPTH_TEST);
}