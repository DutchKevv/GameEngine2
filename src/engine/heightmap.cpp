#include <vector>
#include <random>
#include <iostream>
#include "./renderObject.cpp"
#include <glm/glm.hpp>

class Heightmap : public RenderObject
{
public:
	struct HillAlgorithmParameters
	{
		HillAlgorithmParameters(int rows, int columns, int numHills, int hillRadiusMin, int hillRadiusMax, float hillMinHeight, float hillMaxHeight)
		{
			this->rows = rows;
			this->columns = columns;
			this->numHills = numHills;
			this->hillRadiusMin = hillRadiusMin;
			this->hillRadiusMax = hillRadiusMax;
			this->hillMinHeight = hillMinHeight;
			this->hillMaxHeight = hillMaxHeight;
		}

		int rows;
		int columns;
		int numHills;
		int hillRadiusMin;
		int hillRadiusMax;
		float hillMinHeight;
		float hillMaxHeight;
	};

	Heightmap(const HillAlgorithmParameters &params, bool withPositions = true, bool withTextureCoordinates = true, bool withNormals = true);

	void Heightmap::createFromHeightData(const std::vector > &heightData)
	{
		if (_isInitialized)
		{
			deleteMesh();
		}

		_heightData = heightData;
		_rows = _heightData.size();
		_columns = _heightData[0].size();
		_numVertices = _rows * _columns;

		// First, prepare VAO and VBO for vertex data
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		_vbo.createVBO(_numVertices * getVertexByteSize()); // Preallocate memory
		_vbo.bindVBO();

		if (hasPositions())
		{
			setUpVertices();
		}

		if (hasTextureCoordinates())
		{
			setUpTextureCoordinates();
		}

		if (hasNormals())
		{
			if (!hasPositions())
			{
				setUpVertices();
			}

			setUpNormals();
		}

		setUpIndexBuffer();

		// Clear the data, we won't need it anymore
		_vertices.clear();
		_textureCoordinates.clear();
		_normals.clear();

		// If get here, we have succeeded with generating heightmap
		_isInitialized = true;
	}

	// void render() const override;
	// void renderPoints() const override;

	int getRows() const;
	int getColumns() const;
	float getHeight(const int row, const int column) const;

	std::vector Heightmap::generateRandomHeightData(const HillAlgorithmParameters &params)
	{
		std::vector heightData(params.rows, std::vector(params.columns, 0.0f));

		std::random_device rd;
		std::mt19937 generator(rd());
		std::uniform_int_distribution hillRadiusDistribution(params.hillRadiusMin, params.hillRadiusMax);
		std::uniform_real_distribution hillHeightDistribution(params.hillMinHeight, params.hillMaxHeight);
		std::uniform_int_distribution hillCenterRowIntDistribution(0, params.rows - 1);
		std::uniform_int_distribution hillCenterColIntDistribution(0, params.columns - 1);

		for (int i = 0; i < params.numHills; i++)
		{
			const auto hillCenterRow = hillCenterRowIntDistribution(generator);
			const auto hillCenterCol = hillCenterColIntDistribution(generator);
			const auto hillRadius = hillRadiusDistribution(generator);
			const auto hillHeight = hillHeightDistribution(generator);

			for (auto r = hillCenterRow - hillRadius; r < hillCenterRow + hillRadius; r++)
			{
				for (auto c = hillCenterCol - hillRadius; c < hillCenterCol + hillRadius; c++)
				{
					if (r < 0 || r >= params.rows || c < 0 || c >= params.columns)
					{
						continue;
					}
					const auto r2 = hillRadius * hillRadius; // r*r term
					const auto x2x1 = hillCenterCol - c;	 // (x2-x1) term
					const auto y2y1 = hillCenterRow - r;	 // (y2-y1) term
					const auto height = float(r2 - x2x1 * x2x1 - y2y1 * y2y1);
					if (height < 0.0f)
					{
						continue;
					}
					const auto factor = height / r2;
					heightData[r][c] += hillHeight * factor;
					if (heightData[r][c] > 1.0f)
					{
						heightData[r][c] = 1.0f;
					}
				}
			}
		}
		return heightData;
	}

private:
	void setUpVertices();
	void setUpTextureCoordinates();
	void setUpNormals();
	void setUpIndexBuffer();

	std::vector<glm::vec3> _heightData;
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _textureCoordinates;
	std::vector<glm::vec3> _normals;
	int _rows = 0;
	int _columns = 0;
};