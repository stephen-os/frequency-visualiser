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
    float freq = u_Period / 6.2831;
    float phase = freq * v_UV.x + u_Time;

    float waveIndex = floor(phase);
    float square = mod(waveIndex, 2.0) == 0.0 ? 1.0 : -1.0;

    // Horizontal line
    float y = 0.5 + u_Amplitude * square;
    float yDist = abs(v_UV.y - y);

    // Vertical transition line
    float transitionX = (waveIndex - u_Time) / freq;
    float xDist = abs(v_UV.x - transitionX);

    float topY = 0.5 + u_Amplitude;
    float bottomY = 0.5 - u_Amplitude;
    bool inVerticalBand = v_UV.y >= bottomY && v_UV.y <= topY;

    if (yDist < u_Thickness || (xDist < u_Thickness && inVerticalBand))
        FragColor = vec4(u_Color, 1.0);
    else
        discard;
}
