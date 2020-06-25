#version 330 core
out vec4 FragColor;

in vec3 Normal;

const vec3 LightDir = vec3(0.5, -0.3, -0.4);
const vec3 Color = vec3(0.5, 0.5, 0.5);

void main()
{
    vec3 N = normalize(Normal);
    vec3 Ambient = 0.3 * Color;
    vec3 Diffuse = max(0.0, dot(N, -normalize(LightDir))) * Color;

    FragColor = vec4(Ambient + Diffuse, 1.0);
}