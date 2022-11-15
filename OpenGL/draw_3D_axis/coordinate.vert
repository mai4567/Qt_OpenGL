#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 common_view;

void main()
{
    gl_Position = projection *view *common_view*vec4(aPos, 1.0);
    ourColor = aColor;
}
