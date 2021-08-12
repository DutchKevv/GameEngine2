#include <iostream>

#include <glad/glad.h>

#include "./world.h"
#include "../../engine/camera.h"
#include "../../engine/engine.h"
#include "../../engine/context.h"

const unsigned int SHADOW_WIDTH = 10240, SHADOW_HEIGHT = 10240;
vector<glm::vec4> treePositions;
const unsigned int space = 1330;
const unsigned int trees = 300;
const unsigned int trees2 = 399;
const unsigned int trees3 = 199;
const unsigned int rocks = 75;

void WorldScene::init()
{		
	shader = context->resourceManager->loadShader("shadow");
	depthShader = context->resourceManager->loadShader("shadow_depth");
    
	std::cout << shader->ID << "\n";

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
	// floor = new ShapePlane();
	cube1 = new ShapeCube();
	// cube2 = new ShapeCube();
	// cube3 = new ShapeCube();

	heightMap = new HeightMap();

	// load models
	// -----------

	// player
	player = new Player("game/models/player/vampire/vampire.dae", 1);
	// player->setAnimation("game/models/player/vampire/vampire.dae");
	camera = new Camera(glm::vec3(0.0f, 22.0f, 30.0f));

	// town1 = new Town();
	// town1->position = glm::vec3(210.0f, 1.0f, 20.0f);
	// // town1->init();

	// town2 = new Town();
	// town2->position = glm::vec3(-210.0f, 1.0f, 20.0f);
	// // town2->init();


	// town3 = new Town();
	// camera->followObject(cube1);
	// player->scale = glm::vec3(0.01f);

	// test = new Model("game/models/trees/cartoon/CartoonTree.fbx");
	// treeModel2 = new Model("game/models/cube/cube.obj", 1);
	// tree = new Model("game/models/tree-low-poly/tree.obj", 1000);
	// treeModel = new Model("game/models/tree-low-poly/polytree1.obj", 1000);
	// treeModel3 = new Model("game/models/tree-low-poly/polytree4.obj", 1000);
	// bush = new Model("game/models/house/lowpolybush1.obj", 10000);
	// house = new Model("game/models/house/polyhouse1.1.obj", 50);
	// // treeModel2 = new Model("game/models/tree-low-poly/pinetree2withrocks.obj", 10000);
	// treeModel2 = new Model("game/models/tree-low-poly/pinetree2.obj", 1000);
	sun = new Model("game/models/sphere/sphere.obj", 1);
	// terrain2 = new Terrain2();
	// castle = new Model("game/models/castle/tower/medieval_tower_2.obj", 1);
	// castle->position = glm::vec3(130.0f, 1.0f, 0.0f);
	// castle1 = new Model("game/models/castle/tower/medieval_tower_2.obj", 1);
	// 	castle1->position = glm::vec3(-210.0f, 1.0f, 20.0f);
	// castle2 = new Model("game/models/castle/tower/medieval_tower_2.obj", 1);
	// castle3 = new Model("game/models/castle/tower/medieval_tower_2.obj", 1);

	// treeModel2 = new Model("game/models/tree-low-poly/polytree1.obj", 10000);
	// treeModel2 = new Model("game/models/plane/FREOBJ.obj", 2);
	// rockModel = new Model("game/models/stone/stone.obj");
	// treeModel = new Model("game/models/tree-low-poly/lowpolytree.obj");
	// treeModel = new Model("game/models/tree-low-poly/polytree1.obj");

	// cube2->position = glm::vec3(2.0f, 20.0f, -15.0f);
	// cube3->position = glm::vec3(-1.5f, 20.0f, -2.5f);
	// test->position = glm::vec3(1.0f, 2.0f, 0.0f);



	// addChild(spotlight, this);
		// addChild(sun, this);

	addChild(heightMap, this);
	addChild(cube1, this);
	// addChild(skybox, this);

	// addChild(floor, this);
	// addChild(treeModel2, this);
	// addChild(treeModel, this);
	// addChild(tree, this);

	// addChild(town1, this);
	// addChild(town2, this);
	// addChild(town3, this);
	// addChild(town3, this);
	// addChild(bush, this);
	// addChild(house, this);
	// addChild(castle, this);
	// addChild(castle1, this);
	// addChild(castle2, this);
	// addChild(castle3, this);
	// addChild(player, this);

	// addChild(terrain2, this);
	// addChild(npc, this);

	// addChild(cube2, this);
	// addChild(cube3, this);
	// addChild(test, this);



	// std::cout << "town:  " << town1->id << "\n";

	// town2->warWith = town1->id;
	// town1->warWith = town2->id;

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

	Scene::init();
}

void WorldScene::draw(float delta)
{
	// 1. render depth of scene to texture (from light's perspective)
	// --------------------------------------------------------------
	// shader->setBool("useTexture", true);

	// render
	// ------
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 0.0f, far_plane = 750.5f;

	// lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
	lightProjection = glm::ortho(-580.0f, 580.0f, -580.0f, 580.0f, near_plane, far_plane);
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
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	renderScene(delta, depthShader, true);
	// glCullFace(GL_BACK); // don't forget to reset original culling face
	// glDisable(GL_CULL_FACE);

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

	Scene::draw(delta);
}

// renders the 3D scene
// --------------------
void WorldScene::renderScene(float delta, Shader *shader, bool isShadowRender)
{
	// std::cout << "render world scene \n";
	
	shader->use();
	glEnable(GL_DEPTH_TEST);

	// sun->position = glm::vec3(spotlight->position.x, spotlight->position.y, spotlight->position.z);
	
	Scene::renderScene(delta, shader, isShadowRender);

	glDisable(GL_DEPTH_TEST);
}