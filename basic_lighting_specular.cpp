// CK_head.h ��
// ��ͷ����
// ����ԭ�ͼ�ʵ��
// ȫ�ֱ���
#include "CK_head.h"

// �������㻺����󣬶����������
GLuint VBO, VAO;

GLfloat pi = 3.1415926;
GLfloat degToRad(GLfloat degree) {
	GLfloat radian = degree * pi / 180.0;
	return radian;
}

void setVerts() {
	// 6.0 ���ö�������
	GLfloat r = 0.5f;
	
	GLfloat vertices[] = {
		// λ��				// color
		 sin(degToRad(  0.0))*r, cos(degToRad(  0.0))*r, 0.0,	1.0, 0.0, 0.0,
		 sin(degToRad(120.0))*r, cos(degToRad(120.0))*r, 0.0,	0.0, 1.0, 0.0,
		 sin(degToRad(240.0))*r, cos(degToRad(240.0))*r, 0.0,	0.0, 0.0, 1.0
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
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// 6.4 ��� VAO
	glBindVertexArray(0);
}

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

		// ��ȡunifrom�ĵ�ַ
		// ...
											
		// 7.32 ʹ������Ԫ������
		// ...

		// 7.33 ������Ⱦ��
		surfaceShader.Use();

		// ����unifrom��ֵ�����뼤����ɫ����
		// ...

		// �����任
		glm::mat4 transform; // 4*4��λ����

		// ��ת����
		transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 1.0f, glm::vec3(0.0f, 0.0f, -1.0f));

		// ƽ�ƾ�����ƽ�Ƶ����ĵ㣬Ȼ����ת��
		//transform = glm::translate(transform, glm::vec3(0.0f, 0.15f, 0.0f));

		// ����uniform�����ĵ�ַ
		GLint transformLoc = glGetUniformLocation(surfaceShader.Program, "transform");
		// �Ѿ��󴫵ݸ���ɫ�� 
		// ����1��uniform�ĵ�ַ(Location)
		// ����2����Ҫ���Ͷ��ٸ�����Ŀǰ��1
		// ����3��ѯ�����������Ƿ�ϣ�������ǵľ�������û�(Transpose)��Ҳ����˵�������Ǿ�����к��С�
		// OpenGL������ͨ��ʹ��һ���ڲ����󲼾ֽ�������Ϊ��˳���(Column-major Ordering)���֡�
		// GLM�Ѿ���������Ϊ��˳���������ľ������Բ�����Ҫ�û�����������GL_FALSE��
		// ����4����ʵ�ʵľ������ݣ�����GLM�����ǰ����ǵľ��󴢴�ΪOpenGL��ϣ�������֣�
		// �������Ҫ����GLM���Դ��ĺ���value_ptr���任��Щ���ݡ�
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// 7.35 ��ʼ����
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// ������Ļ������
		glfwSwapBuffers(window);
	}
	// 8.0 �ͷ���Դ
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;

}

