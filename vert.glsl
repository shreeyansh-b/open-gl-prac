#version 330 core
layout (location = 0) in vec3 aPos; // a means attribute i.e. attributePosition;
layout (location = 1) in vec3 aNormal; // a means attribute i.e. attributeNormal;
layout (location = 2) in vec2 aTexCoord; // a means attribute i.e. attibuteTextureCoordinates;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
    TexCoords = aTexCoord;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}