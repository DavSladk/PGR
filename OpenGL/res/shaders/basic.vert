#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texType;

out vec2 v_TexCoord;
out float v_TexType;

void main()
{
   gl_Position = position;
   v_TexCoord = texCoord;
   v_TexType = texType;
};