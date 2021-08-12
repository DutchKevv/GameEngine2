#pragma once

#include <glm/glm.hpp>
#include "../../engine/scene.h"
#include "../../engine/skybox.h"
#include "../../engine/model.h"
#include "../../engine/shader.h"
#include "../../engine/player.h"
#include "../../engine/terrain2.h"
#include "../../engine/heightmap2.cpp"
#include "../../engine/npc.h"
#include "../../shape/cube.h"
#include "../../shape/plane.h"
#include "../../lights/spotlight.cpp"
#include "../town.h"

class WorldScene : public Scene
{
public:
	unsigned int depthMapFBO;
	unsigned int depthMap;
	unsigned int depthCubemap;

	Shader *shader;
	Shader *depthShader;
	ShapeCube *cube1;
	ShapeCube *cube2;
	ShapeCube *cube3;
	Spotlight *spotlight;
	ShapePlane *floor;
	SkyBox *skybox;
	Model *sun;
	Town *town1;
	Town *town2;
	Town *town3;
	Model *castle;
	Model *castle1;
	Model *castle2;
	Model *castle3;
	Model *castle4;
	Model *treeModel;
	Model *treeModel2;
	Model *treeModel3;
	Model *rockModel;
	Model *tree;
	Model *bush;
	Model *house;
	Model *test;
	Player *player;
	Terrain2 *terrain2;

	HeightMap *heightMap;

	vector<glm::vec4> treePositions;
	vector<glm::vec4> treePositions2;
	vector<glm::vec4> rockPositions;
	vector<Npc *> npcs;

	void init();

	void draw(float delta);

	void renderScene(float delta, Shader *shader, bool isShadowRender);
};