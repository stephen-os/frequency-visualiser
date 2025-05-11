#version 430 core

in vec2 v_UV;
out vec4 FragColor;

uniform float u_Time;

void main()
{
    // Compute a sine wave with time-based phase shift
    float y = 0.5 + 0.4 * sin(10.0 * v_UV.x + u_Time); // wave in [0.1, 0.9]

    // Check if the current fragment's vertical coordinate is close to the sine curve
    float thickness = 0.01;
    float dist = abs(v_UV.y - y);

    // If the fragment is close enough to the sine line, color it green, else black
    if (dist < thickness)
        FragColor = vec4(0.0, 1.0, 0.0, 1.0); // green
    else
        FragColor = vec4(0.0, 0.0, 0.0, 1.0); // black
}