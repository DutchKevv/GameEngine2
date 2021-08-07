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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./mesh.h"
#include "./shader.cpp"
#include "./renderObject.h"
#include "assimp/assimp_glm_helpers.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// #include "./animator.h"
#include "animdata.h"

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
	unsigned int buffer;
	
	const unsigned int space = 1730;

	// Animation *danceAnimation;
	// Animator *animator;

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
	auto& GetOffsetMatMap() { return m_OffsetMatMap; }
	int& GetBoneCount() { return m_BoneCount; }

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

	void SetVertexBoneData(Vertex& vertex, int boneID, float weight)
	{
		for (int i = 0; i < AI_MAX_BONE_WEIGHTS; ++i)
		{
			if (vertex.m_BoneIDs[i] < 0)
			{
				vertex.m_Weights[i] = weight;
				vertex.m_BoneIDs[i] = boneID;
				break;
			}
		}
	}


	void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene)
	{
		auto& boneInfoMap = m_OffsetMatMap;
		int& boneCount = m_BoneCount;

		for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
		{
			int boneID = -1;
			std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
			if (boneInfoMap.find(boneName) == boneInfoMap.end())
			{
				BoneInfo newBoneInfo;
				newBoneInfo.id = boneCount;
				newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
				boneInfoMap[boneName] = newBoneInfo;
				boneID = boneCount;
				boneCount++;
			}
			else
			{
				boneID = boneInfoMap[boneName].id;
			}
			assert(boneID != -1);
			auto weights = mesh->mBones[boneIndex]->mWeights;
			int numWeights = mesh->mBones[boneIndex]->mNumWeights;

			for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
			{
				int vertexId = weights[weightIndex].mVertexId;
				float weight = weights[weightIndex].mWeight;
				assert(vertexId <= vertices.size());
				SetVertexBoneData(vertices[vertexId], boneID, weight);
			}
		}
	}
};