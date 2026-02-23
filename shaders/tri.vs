#version 330 core
layout (location = 0) in vec2 inPos;
layout (location = 1) in float inValue;

uniform float minX;
uniform float minY;
uniform float maxY;
uniform float maxX;
uniform float minValue;
uniform float maxValue;
uniform vec3 minColor;
uniform vec3 maxColor;

out vec3 outColor;

void main()
{
    gl_Position = vec4((inPos.x - minX) / (maxX - minX) * 2.0 - 1.0, (inPos.y - minY) / (maxY - minY) * 2.0 - 1.0, 0.0, 1.0);
    // gl_Position = vec4(inPos.x, inPos.y, 0.0, 1.0);
    outColor = mix(minColor, maxColor, (inValue - minValue) / (maxValue - minValue));
    // outColor = maxColor;
}