#version 430 core

layout(location = 0) in vec2 a_Position;

out vec2 v_UV;

void main()
{
    // Map vertex positions to UV coords from 0.0 to 1.0
    v_UV = a_Position * 0.5 + 0.5;
    gl_Position = vec4(a_Position, 0.0, 1.0);
}