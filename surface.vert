#version 330 core

// 顶点数据
layout (location = 0) in vec3 position; // 数据位0 位置
layout (location = 1) in vec3 color;    // 数据位1 颜色

out vec3 ourColor;

uniform mat4 transform; // 矩阵

void main()
{
	gl_Position = transform * vec4(position, 1.0f); 
	ourColor = color;
}