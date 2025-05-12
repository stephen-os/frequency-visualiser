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
    float TWO_PI = 6.2831;
    float freq = u_Period / TWO_PI;

    // Calculate wrapped X for sawtooth
    float wrappedX = mod(u_Period * v_UV.x + u_Time, TWO_PI);
    float normalized = wrappedX / TWO_PI;
    float y = 0.5 + u_Amplitude * (2.0 * normalized - 1.0);
    float yDist = abs(v_UV.y - y);

    // The current wave index in UV space
    float basePhase = u_Period * v_UV.x + u_Time;
    float waveIndex = floor(basePhase / TWO_PI);
    
    // This gives the exact UV.x where the wave resets
    float transitionX = (TWO_PI * waveIndex - u_Time) / u_Period;
    float xDist = abs(v_UV.x - transitionX);

    float topY = 0.5 + u_Amplitude;
    float bottomY = 0.5 - u_Amplitude;
    bool inVerticalBand = v_UV.y >= bottomY && v_UV.y <= topY;

    if (yDist < u_Thickness || (xDist < u_Thickness && inVerticalBand))
        FragColor = vec4(u_Color, 1.0);
    else
        discard;
}
