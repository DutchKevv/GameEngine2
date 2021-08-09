#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <assimp/types.h>
#include "./shader.h"
#include "./texture.h"
#include "./context.h"

#define MAX_BONE_INFLUENCE 4

using namespace std;

struct Vertex
{
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	// bitangent
	glm::vec3 Color;

	//bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];

    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	// mesh Data
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	aiColor3D color;
	unsigned int VAO;

	Texture2D *texture;

	// constructor
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, aiColor3D color = aiColor3D(0.0f, 0.4f, 0.3f))
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		this->color = color;

		texture = context->resourceManager->loadTexture("1x1.png", true, "1x1", 0, 0);

		// now that we have all the required data, set the vertex buffers and its attribute pointers.
		setupMesh();
	}

	// render the mesh
	void Draw(Shader *shader, unsigned int amount)
	{
		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;

		shader->setVec3("material.ambient", 0.2f, 0.2f, 0.2);
		shader->setInt("material.diffuse", 0);
		// shader->setVec3("material.specular", 1.0f, 1.0f, 1.0f);
		// shader->setFloat("material.shininess", 10.0f);

		// std::cout << "red: " << color.b << "\n";

		if (textures.size() > 0)
		{
			shader->setBool("useTexture", true);

			for (unsigned int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

				// retrieve texture number (the N in diffuse_textureN)
				string number;
				string name = textures[i].type;
				if (name == "texture_diffuse") {
					number = std::to_string(diffuseNr++);
					shader->setFloat(("material.diffuse"), i);
				}
				else if (name == "texture_specular")
					number = std::to_string(specularNr++); // transfer unsigned int to stream
				else if (name == "texture_normal")
					number = std::to_string(normalNr++); // transfer unsigned int to stream
				else if (name == "texture_height")
					number = std::to_string(heightNr++); // transfer unsigned int to stream

				shader->setFloat(("material." + name).c_str(), i);
				glBindTexture(GL_TEXTURE_2D, textures[i].id);

				// now set the sampler to the correct texture unit
				// glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()), i);
				// and finally bind the texture
				// glBindTexture(GL_TEXTURE_2D, textures[i].id);
			}
		}
		else
		{
			glActiveTexture(GL_TEXTURE0);
			texture->Bind();
			shader->setVec3("_color", glm::vec3(color.r, color.g, color.b));
			// shader->setVec3("material.diffuse", glm::vec3(color.r, color.g, color.b));
		}

		// draw mesh
		glBindVertexArray(VAO);
		glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, amount);
		// glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}

private:
	// render data
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void setupMesh()
	{
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));
		// vertex tangent
		// glEnableVertexAttribArray(3);
		// glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Tangent));
		// // vertex bitangent
		// glEnableVertexAttribArray(4);
		// glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Bitangent));

		// bone ids
        glEnableVertexAttribArray(7);
        glVertexAttribIPointer(7, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

        // weights
        glEnableVertexAttribArray(8);
        glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));

		glBindVertexArray(0);
	}
};
#endif