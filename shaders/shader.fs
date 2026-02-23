#version 330 core
out vec4 FragColor;

in vec3 outColor;
in vec2 outTexCoord;
uniform sampler2D texture1;  // 【必须完全一致，区分大小写】

void main()
{
//     FragColor = vec4(outColor, 1.0f);
    FragColor = texture(texture1, outTexCoord) * vec4(outColor, 1.0);
}