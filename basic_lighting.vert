// ģ�Ͷ�����ɫ��

#version 330 core

layout (location = 0) in vec3 position; // ����λ0 ����λ��
layout (location = 1) in vec3 normal;   // ����λ1 ��������

out vec3 Normal;         // ������
out vec3 FragPos;        // Ƭ��λ��

uniform mat4 model;      // ģ�;���
uniform mat4 view;       // ��ͼ����
uniform mat4 projection; // ͶӰ����

void main()
{
	// ����������
    gl_Position = projection * view *  model * vec4(position, 1.0f);
	// Ƭ��λ�ü���
    FragPos = vec3(model * vec4(position, 1.0f));
	// ������������任����
	// ��ģ�;��� ������� ,Ȼ����Է�������
	// ʹ������������������һ����о���任
    Normal = mat3(transpose(inverse(model))) * normal;  
} 