#version 330 core
layout (location = 0) in vec3 aPos; // a means attribute i.e. attributePosition;
layout (location = 1) in vec2 aTexCoord; // a means attribute i.e. attibuteTextureCoordinates

out vec2 TexCoord;

void main()
{
    gl_Position = vec4( aPos.x, aPos.y ,aPos.z, 1.0);
    TexCoord = aTexCoord;
}