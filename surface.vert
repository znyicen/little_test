#version 330 core

// ��������
layout (location = 0) in vec3 position; // ����λ0 λ��

void main()
{
	gl_Position = vec4(position, 1.0f); 
}