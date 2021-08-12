#version 330

layout (location = 0) in vec3 aPos;

uniform mat4 modelview;
uniform mat4 project;
uniform mat4 model;
uniform mat4 view;

in float x;
in float y;
in float z;

out mat4 _modelview;

void main()
{
  _modelview = modelview;
  gl_Position = project * modelview * vec4(x, y, z, 1.0);
  // gl_Position = project * view * model * vec4(x, y, z, 1.0);
};