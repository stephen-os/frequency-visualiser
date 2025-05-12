#version 430 core

in vec2 v_UV;

out vec4 FragColor;

uniform float grid_intensity = 0.7;
uniform float grid_size = 0.02;
uniform float line_thickness = 0.002;

void main()
{
    vec2 grid = fract(v_UV / grid_size);
    
    vec2 gridLines = smoothstep(0.0, line_thickness / grid_size, grid) * smoothstep(0.0, line_thickness / grid_size, 1.0 - grid);
    
    float isLine = 1.0 - min(gridLines.x, gridLines.y);
    
    vec3 lineColor = vec3(isLine * grid_intensity);
    
    FragColor = vec4(lineColor, 1.0);
}