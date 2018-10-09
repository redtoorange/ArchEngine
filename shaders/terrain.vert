#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec4 aColor;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 terrainAlbedo;
uniform bool enableGlobalIllumination;
uniform float globalIllumination;

out vec4 color;

void main()
{
    if( enableGlobalIllumination ){
        gl_Position = projection * view * transform * vec4(aPos, 1.0);
        color = terrainAlbedo * globalIllumination;
    }
    else{
        gl_Position = projection * view * transform * vec4(aPos, 1.0);
	    color = terrainAlbedo;
    }
}

