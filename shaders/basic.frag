#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 toLight;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec4 lightColor;

void main()
{    
	vec3 unitNormal = normalize(Normal);
	vec3 unitToLight = normalize(toLight);

	float nDot1 = dot(unitNormal, unitToLight);
	float brightness = max(nDot1, 0.0);
	vec4 diffuse = brightness * lightColor;

    FragColor = diffuse * texture(texture_diffuse1, TexCoords);
}