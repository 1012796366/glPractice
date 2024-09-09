#version 330 core
out vec4 FragColor;

//in vec3 customColor;
in vec2 texCoord;

uniform sampler2D cusTex1;
uniform sampler2D cusTex2;

void main()
{
    FragColor = mix(texture(cusTex1, texCoord), texture(cusTex2, vec2(texCoord.x, texCoord.y)), 0.2);
}