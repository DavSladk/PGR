#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 2) in float texType;

out vec2 v_TexCoord;

void main()
{
   gl_Position = position;
   v_TexCoord = texCoord;
};