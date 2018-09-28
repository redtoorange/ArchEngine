#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;

void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
	color = aColor;
}