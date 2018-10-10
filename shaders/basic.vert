#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out vec3 toLight;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightposition;

out vec4 color;

void main()
{
	vec4 worldPosition = transform * vec4(aPos, 1.0f);
	gl_Position = projection * view * worldPosition;

	Normal = (transform * vec4(aNormal, 0.0)).xyz;
	toLight = lightposition - worldPosition.xyz;
	
	FragPos = vec3(transform * vec4(aPos, 1.0f));
    TexCoords = aTexCoords; 
}