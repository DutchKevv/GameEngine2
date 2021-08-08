#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 3) in mat4 instanceMatrix;
layout (location = 7) in ivec4 boneIds;
layout (location = 8) in vec4 weights;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;

// temp
uniform bool useInstances;
uniform mat4 finalBonesMatrices[MAX_BONES];

void main()
{
    mat4 viewModel;
    if (useInstances) {
        viewModel = lightSpaceMatrix * instanceMatrix;
    } else {
        viewModel = lightSpaceMatrix * model;
    }

    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >= MAX_BONES) 
        {
            totalPosition = vec4(aPos,1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(aPos,1.0f);
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * aNormal;
    }

    gl_Position = viewModel * totalPosition;
}