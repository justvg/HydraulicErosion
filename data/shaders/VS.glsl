#version 330 core
layout (location = 0) in vec3 aP;
layout (location = 1) in vec3 aN;

uniform mat4 Projection = mat4(1.0);
uniform mat4 View = mat4(1.0);
uniform mat4 Model = mat4(1.0);

out vec3 Normal;

void main()
{
    Normal = mat3(Model) * aN;
    gl_Position = Projection * View * Model * vec4(aP, 1.0);
}