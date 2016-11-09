#version 330 core

// 顶点数据
layout (location = 0) in vec3 position; // 数据位0 位置

void main()
{
	gl_Position = vec4(position, 1.0f); 
}