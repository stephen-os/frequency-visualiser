#version 430 core

in vec2 v_UV;
out vec4 FragColor;

uniform float u_Time;
uniform float u_Amplitude;
uniform float u_Period;
uniform float u_Thickness;
uniform vec3  u_Color;

void main()
{
    float y = 0.5 + u_Amplitude * cos(u_Period * v_UV.x + u_Time);
    float dist = abs(v_UV.y - y);
    if (dist < u_Thickness)
        FragColor = vec4(u_Color, 1.0);
    else
        discard;
}
