#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../engine/baseObject.h"
#include "../../engine/scene.h"
#include "../../engine/camera.h"
#include "../../engine/engine.h"
#include "../../engine/context.h"
#include "../../engine/skybox.h"
#include "../../engine/texture.h"
#include "../../engine/model.h"
#include "../../engine/shader.cpp"
// #include "../../engine/heightmap2.cpp"
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

	unsigned int depthMapFBO;
	unsigned int depthMap;
	unsigned int depthCubemap;

	Shader *shader;
	Shader *depthShader;
	Model *treeModel;
	Model *treeModel2;
	Model *rockModel;
	Model *test;
	// HeightMap *heightMap;

	vector<glm::vec4> treePositions;
	vector<glm::vec4> treePositions2;
	vector<glm::vec4> rockPositions;

	Texture2D *texture;

	void init();

	void draw(float delta);

	// renders the 3D scene
	// --------------------
	void renderScene(float delta, Shader *shader, bool isShadowRender);
};