#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexType;
in vec4 v_Color;
in vec3 v_Normal;

uniform sampler2D u_Texture_Metal_Light;
uniform sampler2D u_Texture_Metal_Dark;
uniform sampler2D u_Texture_Wood_Light;
uniform sampler2D u_Texture_Wood_Dark;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    float ambientStrength = 0.1;
    vec4 ambient = vec4(ambientStrength * lightColor, 1.0);

    vec4 texColor;

    if(v_TexType < 0.5)
    {
        texColor = texture(u_Texture_Metal_Light, v_TexCoord);
    }
    else if(v_TexType < 1.5)
    {
        texColor = texture(u_Texture_Metal_Dark, v_TexCoord);
    }
    else if(v_TexType < 2.5)
    {
        texColor = texture(u_Texture_Wood_Light, v_TexCoord);
    }
    else if(v_TexType < 3.5)
    {
        texColor = texture(u_Texture_Wood_Dark, v_TexCoord);
    }
    
    color = v_Color;
    color = ambient * texColor;
};