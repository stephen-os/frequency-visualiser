#version 430 core

out vec4 FragColor;

uniform vec2 u_resolution;       // Resolution of the screen
uniform float u_gridSpacing;     // Spacing between minor grid lines
uniform float u_thickness;       // Thickness of minor grid lines
uniform float u_centerThickness; // Thickness of the central plus

void main() 
{
    vec2 fragCoord = gl_FragCoord.xy;
    vec2 centered = fragCoord - u_resolution * 0.5;

    float lineX = abs(mod(centered.x, u_gridSpacing));
    float lineY = abs(mod(centered.y, u_gridSpacing));

    float minorLine = step(lineX, u_thickness) + step(lineY, u_thickness);
    float centerLine = step(abs(centered.x), u_centerThickness) + step(abs(centered.y), u_centerThickness);

    float intensity = max(minorLine * 0.5, centerLine);

    FragColor = vec4(vec3(intensity), 1.0);
}
