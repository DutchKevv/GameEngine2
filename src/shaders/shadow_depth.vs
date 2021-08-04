#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in mat4 instanceMatrix;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

// temp
uniform bool useInstances;

void main()
{
     if (useInstances) {
        gl_Position = lightSpaceMatrix * instanceMatrix * vec4(aPos, 1.0);
    } else {
        gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
    }

    // gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}