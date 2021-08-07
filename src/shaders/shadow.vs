#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 instanceMatrix;
layout (location = 4) in ivec4 boneIds;
layout (location = 5) in vec4 weights;


out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

// temp
uniform bool useInstances;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

void main()
{
    mat4 viewModel;
    
    if (useInstances) {
        vs_out.FragPos = vec3(instanceMatrix * vec4(aPos, 1.0));
        gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);
        viewModel = view * instanceMatrix;
        // vs_out.Normal = transpose(inverse(mat3(instanceMatrix))) * aNormal;
    } else {
        vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        viewModel = view * model;
        // vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    }

    vec4 totalPosition = vec4(0.0f);
    vec3 localNormal = aNormal;
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
        localNormal = mat3(finalBonesMatrices[boneIds[i]]) * aNormal;
   }

    gl_Position = projection * viewModel * totalPosition;

    vs_out.FragPos = vec3(totalPosition.x, totalPosition.y,totalPosition.z);
    vs_out.Normal = localNormal;
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
}