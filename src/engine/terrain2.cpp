#include "./terrain2.h"
#include "./context.h"

void Terrain2::init()
{
    //  std::cout << "init player \n";

    texture = context->resourceManager->loadTexture("terrain/heightmap.jpg", true, "heightmap", 0, 0);

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
   
    float vertices[64];

// for i in range(64 - 1):
//     for j in range(64):
//         vertices += struct.pack('2f', i / 64, j / 64)
//         indices += struct.pack('i', index)
//         index += 1

//         vertices += struct.pack('2f', (i + 1) / 64, j / 64)
//         indices += struct.pack('i', index)
//         index += 1

//     indices += struct.pack('i', -1)

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


// vbo = ctx.buffer(vertices)
// ibo = ctx.buffer(indices)

// vao = ctx.vertex_array(prog, [(vbo, '2f', ['vert'])], ibo)

    glBindVertexArray(cubeVAO);

    RenderObject::init();
}

void Terrain2::renderScene(float delta, Shader *shader, bool isShadowRender)
{
    shader->setInt("Heightmap", 0);
    // prog.uniforms['Color1'].value = 1;
    // prog.uniforms['Color2'].value = 2;
    // prog.uniforms['Cracks'].value = 3;
    // prog.uniforms['Darken'].value = 4;

    // RenderObject::renderScene(delta, shader, isShadowRender);
}