// CK_head.h ��
// ��ͷ����
// ����ԭ�ͼ�ʵ��
// ȫ�ֱ���
#include "CK_head.h"

// �������㻺����󣬶����������
GLuint VBO, VAO;		    
void setVerts(); 

//// IV ������ ////
int main()
{
	openGL_setup();

	// 5.0 ��д��������ɫ������
	Shader surfaceShader("surface.vert", "surface.frag");

	setVerts();

	// 7.0 ��Ϸѭ��
	while (!glfwWindowShouldClose(window))
	{
		// 7.1 ���㵱ǰ֡��deltaTime
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 7.2 ��������¼�
		glfwPollEvents();
		// ��������
		do_movement();

		// 7.3 ��Ⱦ
		// 7.31 �����ɫ������
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����Ȼ�����

		// 7.32 ʹ������Ԫ������
		// ...

		// 7.33 ������Ⱦ��
		surfaceShader.Use();

		// 7.35 ��ʼ����
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		
		// *ʹ��EBO�Ļ���
		// glBindVertexArray(VAO); // ��VAO
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glBindVertexArray(0);   // ���

		// ������Ļ������
		glfwSwapBuffers(window);
	}
	// 8.0 �ͷ���Դ
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;

}

void setVerts() {
	// 6.0 ���ö�������
	GLfloat vertices[] = {
		// λ��               // ������
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	};

	// 6.1 �������ݶ���
	glGenVertexArrays(1, &VAO);	// ���ɻ���ID
	glGenBuffers(1, &VBO);		// ���ɻ���ID

	// 6.2 �����ݶ���
	// ����VAO
	glBindVertexArray(VAO);

	// ����VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ����EBO
	// ...

	// 6.3 ���Ͷ������ݣ����ݵģ�λ�á���λ����ʽ������������ƫ������
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// ��������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)
		(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// 6.4 ��� VAO
	glBindVertexArray(0);
}