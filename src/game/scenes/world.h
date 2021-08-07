#pragma once

#include <glm/glm.hpp>
#include "../../engine/scene.h"
#include "../../engine/skybox.h"
#include "../../engine/texture.h"
#include "../../engine/model.h"
#include "../../engine/shader.cpp"
#include "../../engine/animator.h"
#include "../../shape/cube.h"
#include "../../shape/plane.h"
#include "../../lights/spotlight.cpp"

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
	Model *sun;
	Model *castle;

	unsigned int depthMapFBO;
	unsigned int depthMap;
	unsigned int depthCubemap;

	Shader *shader;
	Shader *depthShader;
	Model *treeModel;
	Model *treeModel2;
	Model *treeModel3;
	Model *rockModel;
	Model *test;
	Model *player;
	Animation *danceAnimation;
	Animator *animator;
	// HeightMap *heightMap;

	vector<glm::vec4> treePositions;
	vector<glm::vec4> treePositions2;
	vector<glm::vec4> rockPositions;

	void init();

	void draw(float delta);

	// renders the 3D scene
	// --------------------
	void renderScene(float delta, Shader *shader, bool isShadowRender);
};