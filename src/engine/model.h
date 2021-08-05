#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// #include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./mesh.h"
#include "./shader.cpp"
#include "./renderObject.h"

using namespace std;

class Model : public RenderObject
{
public:
	// model data
	vector<Texture> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;
	unsigned int amount;
	glm::mat4 *modelMatrices;

	const unsigned int space = 9330;

	// constructor, expects a filepath to a 3D model.
	Model(string const &path, unsigned int _amount = 1, bool gamma = false) : gammaCorrection(gamma)
	{
		// std::cout << "init model1 \n";

		amount = _amount;

		loadModel(path);
	}

	void init();

	// draws the model, and thus all its meshes
	void renderScene(float delta, Shader *shader, bool isShadowRender);

private:
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(string const &path);

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode *node, const aiScene *scene);

	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};