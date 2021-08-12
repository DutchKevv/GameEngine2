#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 instanceMatrix;
layout (location = 7) in ivec4 boneIds;
layout (location = 8) in vec4 weights;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

// uniform sampler2D Heightmap;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

// temp
uniform bool useInstances;
in vec2 vert;

vec4 BonesCalculation()
{
    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) {
            if (i == 0) {
                totalPosition = vec4(aPos,1.0f);
            }
            continue;
        }
        if(boneIds[i] >= MAX_BONES) 
        {
            totalPosition = vec4(aPos,1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(aPos,1.0f);
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * aNormal;
    }

    return totalPosition;
}

void main()
{
    mat4 localModel = useInstances ? instanceMatrix : model;
    // vec4 vertex = vec4(vert - 0.5, texture(Heightmap, vert).r * 0.2, 1.0);

    gl_Position = projection * view * localModel * BonesCalculation();

    // vs_out.Normal = transpose(inverse(mat3(localModel))) * aNormal;
    vs_out.Normal = aNormal;
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPos = vec3(localModel * vec4(aPos, 1.0));
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
}