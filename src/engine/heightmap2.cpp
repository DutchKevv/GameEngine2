#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stddef.h>
#include <iostream>
#include "./renderObject.cpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./shader.h"
#include "./context.h"

/* Map height updates */
#define MAX_CIRCLE_SIZE (5.0f)
#define MAX_DISPLACEMENT (1.0f)
#define DISPLACEMENT_SIGN_LIMIT (0.3f)
#define MAX_ITER (200)
#define NUM_ITER_AT_A_TIME (1)

/* Map general information */
#define MAP_SIZE (10.0f)
#define MAP_NUM_VERTICES (80)
#define MAP_NUM_TOTAL_VERTICES (MAP_NUM_VERTICES * MAP_NUM_VERTICES)
#define MAP_NUM_LINES (3 * (MAP_NUM_VERTICES - 1) * (MAP_NUM_VERTICES - 1) + 2 * (MAP_NUM_VERTICES - 1))

static GLfloat map_vertices[3][MAP_NUM_TOTAL_VERTICES];
static GLuint map_line_indices[2 * MAP_NUM_LINES];

/* Model view matrix */
static GLfloat modelview_matrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    -5.0f, -5.0f, -20.0f, 1.0f};

/* Frustum configuration */
static GLfloat view_angle = 45.0f;
static GLfloat aspect_ratio = 4.0f / 3.0f;
static GLfloat z_near = 1.0f;
static GLfloat z_far = 100.f;

class HeightMap : public RenderObject
{
    Shader *shader;
    GLint uloc_modelview;
    GLint uloc_project;
    GLuint VBO[4];
    GLuint VAO;
    int iter = 0;
    double dt;
    double last_update_time = glfwGetTime();
    int frame = 0;
    float f;

    Texture2D *texture;

    void init()
    {
        std::cout << "init floor \n";

        // shader
        shader = context->resourceManager->loadShader("heightmap");
        shader->use();

        texture = context->resourceManager->loadTexture("sand.jpg", true, "grass2", 0, 0);

        std::cout << shader->ID << "\n";

        uloc_modelview = glGetUniformLocation(shader->ID, "modelview");
        uloc_project = glGetUniformLocation(shader->ID, "project");

        std::cout << "project loc: " << uloc_project << "\n";
        std::cout << "modelview loc: " << uloc_modelview << "\n";

        /* Set the camera position */
        // modelview_matrix[12] = -5.0f;
        // modelview_matrix[13] = -5.0f;
        // modelview_matrix[14] = -20.0f;
        glUniformMatrix4fv(uloc_modelview, 1, GL_FALSE, modelview_matrix);

        /* Create mesh data */
        initMap();
        makeMesh();

        RenderObject::init();
    }

    /* Generate vertices and indices for the heightmap
 */
    void generate_heightmap__circle(float *center_x, float *center_y,
                                    float *size, float *displacement)
    {
        float sign;
        /* random value for element in between [0-1.0] */
        *center_x = (MAP_SIZE * rand()) / (float)RAND_MAX;
        *center_y = (MAP_SIZE * rand()) / (float)RAND_MAX;
        *size = (MAX_CIRCLE_SIZE * rand()) / (float)RAND_MAX;
        sign = (1.0f * rand()) / (float)RAND_MAX;
        sign = (sign < DISPLACEMENT_SIGN_LIMIT) ? -1.0f : 1.0f;
        *displacement = (sign * (MAX_DISPLACEMENT * rand())) / (float)RAND_MAX;
    }

    /* Run the specified number of iterations of the generation process for the
 * heightmap
 */
    void updateMap(int num_iter)
    {
        assert(num_iter > 0);

        while (num_iter)
        {
            /* center of the circle */
            float center_x;
            float center_z;
            float circle_size;
            float disp;
            size_t ii;
            generate_heightmap__circle(&center_x, &center_z, &circle_size, &disp);
            disp = disp / 2.0f;
            for (ii = 0u; ii < MAP_NUM_TOTAL_VERTICES; ++ii)
            {
                GLfloat dx = center_x - map_vertices[0][ii];
                GLfloat dz = center_z - map_vertices[2][ii];
                GLfloat pd = (2.0f * (float)sqrt((dx * dx) + (dz * dz))) / circle_size;
                if (fabs(pd) <= 1.0f)
                {
                    /* tx,tz is within the circle */
                    GLfloat new_height = disp + (float)(cos(pd * 3.14f) * disp);
                    map_vertices[1][ii] += new_height;
                }
            }
            --num_iter;
        }
    }

    void makeMesh()
    {
        GLuint attrloc;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(4, VBO);
        glBindVertexArray(VAO);

        /* Prepare the data for drawing through a buffer inidices */
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[3]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * MAP_NUM_TOTAL_VERTICES * 4, map_line_indices, GL_STATIC_DRAW);

        /* Prepare the attributes for rendering */
        attrloc = glGetAttribLocation(shader->ID, "x");
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[0][0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(attrloc);
        glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);
        std::cout << attrloc << "\n";

        attrloc = glGetAttribLocation(shader->ID, "z");
        glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[2][0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(attrloc);
        glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);
        std::cout << attrloc << "\n";

        attrloc = glGetAttribLocation(shader->ID, "y");
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[1][0], GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(attrloc);
        glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);
        std::cout << attrloc << "\n";
    }

    void updateMesh()
    {
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[1][0]);
    }

    void renderScene(float delta, Shader *_shader, bool isShadowRender)
    {
        if (isShadowRender)
        {
            return;
        }

        ++frame;

        shader->use();

        glActiveTexture(GL_TEXTURE0);
        texture->Bind();

        float ratio = (float)context->display->windowW / (float)context->display->windowH;
        glm::mat4 projection = glm::perspective(glm::radians(scene->camera->Zoom), ratio, 1.1f, 10000.0f);
        glm::mat4 view = scene->camera->GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-5.0f, -5.0f, -20.0f));
        // model = glm::translate(model, glm::vec3(-5.0f, -5.0f, -20.0f));

        glBindVertexArray(VAO);

        shader->setMat4("project", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", model);

        // glDrawArrays(GL_TRIANGLES, 0, MAP_NUM_TOTAL_VERTICES);
        glDrawElements(GL_TRIANGLES, 4 * MAP_NUM_TOTAL_VERTICES, GL_UNSIGNED_INT, 0);

        dt = glfwGetTime();
        if ((dt - last_update_time) > 0.2)
        {
            /* generate the next iteration of the heightmap */
            if (iter < MAX_ITER)
            {
                updateMap(NUM_ITER_AT_A_TIME);
                updateMesh();
                // std::cout << shader->ID << "\n";
                iter += NUM_ITER_AT_A_TIME;
            }
            last_update_time = dt;
            frame = 0;
        }

        _shader->use();
    }

private:
    void initMap(void)
    {
        int i;
        int j;
        int k;
        GLfloat step = MAP_SIZE / (MAP_NUM_VERTICES - 1);
        GLfloat x = 0.0f;
        GLfloat z = 0.0f;

        /* Create a flat grid */
        k = 0;
        for (i = 0; i < MAP_NUM_VERTICES; ++i)
        {
            for (j = 0; j < MAP_NUM_VERTICES; ++j)
            {
                map_vertices[0][k] = x;
                map_vertices[1][k] = 0.0f;
                map_vertices[2][k] = z;
                z += step;
                ++k;
            }
            x += step;
            z = 0.0f;
        }

        /* close the top of the square */
        k = 0;
        for (i = 0; i < MAP_NUM_VERTICES - 1; ++i)
        {
            map_line_indices[k++] = (i + 1) * MAP_NUM_VERTICES - 1;
            map_line_indices[k++] = (i + 2) * MAP_NUM_VERTICES - 1;
        }
        /* close the right of the square */
        for (i = 0; i < MAP_NUM_VERTICES - 1; ++i)
        {
            map_line_indices[k++] = (MAP_NUM_VERTICES - 1) * MAP_NUM_VERTICES + i;
            map_line_indices[k++] = (MAP_NUM_VERTICES - 1) * MAP_NUM_VERTICES + i + 1;
        }

        for (i = 0; i < (MAP_NUM_VERTICES - 1); ++i)
        {
            for (j = 0; j < (MAP_NUM_VERTICES - 1); ++j)
            {
                int ref = i * (MAP_NUM_VERTICES) + j;
                map_line_indices[k++] = ref;
                map_line_indices[k++] = ref + 1;

                map_line_indices[k++] = ref;
                map_line_indices[k++] = ref + MAP_NUM_VERTICES;

                map_line_indices[k++] = ref;
                map_line_indices[k++] = ref + MAP_NUM_VERTICES + 1;
            }
        }
    }
};
