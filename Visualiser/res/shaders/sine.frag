#version 430 core

in vec2 v_UV;
out vec4 FragColor;

uniform float u_Time;
uniform float u_Amplitude; // e.g. 0.4
uniform float u_Period;    // e.g. 10.0
uniform float u_Thickness; // e.g. 0.01
uniform vec3  u_Color;     // e.g. vec3(0.0, 1.0, 0.0)

void main()
{
    // Compute sine wave Y position with amplitude and period
    float y = 0.5 + u_Amplitude * sin(u_Period * v_UV.x + u_Time);

    // Compute distance from fragment's Y to sine curve
    float dist = abs(v_UV.y - y);

    // Render if within thickness threshold
    if (dist < u_Thickness)
        FragColor = vec4(u_Color, 1.0);
    else
        discard;
}
