#pragma once

#include <map>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./mesh.h"
#include "./shader.h"
#include "./renderObject.h"
#include "./animdata.h"
// #include "./animation.h"
// #include "./animator.h"

class Animation;
class Animator;

using namespace std;

class Model : public RenderObject
{
public:
	vector<Texture> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;
	glm::mat4 *modelMatrices;
	unsigned int amount;
	unsigned int instanceBuffer;

	Animation *animation;
    Animator *animator = NULL;
	vector<glm::mat4> finalBonesMatrices;

	const unsigned int space = 1730;

	// constructor, expects a filepath to a 3D model.
	Model(string const &path, unsigned int _amount = 1, bool gamma = false);

	void init();

	void update(float delta);

	// draws the model, and thus all its meshes
	void renderScene(float delta, Shader *shader, bool isShadowRender);

	void setAnimation(string const &path);

	auto &GetOffsetMatMap() { return m_OffsetMatMap; }
	int &GetBoneCount() { return m_BoneCount; }

	
	void SetVertexBoneDataToDefault(Vertex &vertex);

private:
	std::map<string, BoneInfo> m_OffsetMatMap;
	int m_BoneCount = 0;
	
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(string const &path);

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode *node, const aiScene *scene);

	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

	void SetVertexBoneData(Vertex &vertex, int boneID, float weight);

	void ExtractBoneWeightForVertices(std::vector<Vertex> &vertices, aiMesh *mesh, const aiScene *scene);
};