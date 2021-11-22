#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexType;
in vec4 v_Color;

uniform sampler2D u_Texture_Metal;
uniform sampler2D u_Texture_Wood;

void main()
{
    vec4 texColor;

	if(v_TexType > 0.5)
    {
        texColor = texture(u_Texture_Metal, v_TexCoord);
    }
    else
    {
        texColor = texture(u_Texture_Wood, v_TexCoord);
    }
    
    color = v_Color;
    color = texColor;
};