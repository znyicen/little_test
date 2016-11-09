// CK_head.h ：
// 库头引用
// 函数原型及实现
// 全局变量
#include "CK_head.h"

// 创建顶点缓存对象，顶点数组对象
GLuint VBO, VAO;		    
void setVerts(); 

//// IV 主程序 ////
int main()
{
	openGL_setup();

	// 5.0 编写并编译着色器程序
	Shader surfaceShader("surface.vert", "surface.frag");

	setVerts();

	// 7.0 游戏循环
	while (!glfwWindowShouldClose(window))
	{
		// 7.1 计算当前帧的deltaTime
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 7.2 检测输入事件
		glfwPollEvents();
		// 按键处理
		do_movement();

		// 7.3 渲染
		// 7.31 清空颜色缓冲区
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除深度缓冲区

		// 7.32 使用纹理单元绑定纹理
		// ...

		// 7.33 激活渲染器
		surfaceShader.Use();

		// 7.35 开始绘制
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		
		// *使用EBO的绘制
		// glBindVertexArray(VAO); // 绑VAO
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glBindVertexArray(0);   // 解绑

		// 交换屏幕缓冲区
		glfwSwapBuffers(window);
	}
	// 8.0 释放资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;

}

void setVerts() {
	// 6.0 设置顶点数据
	GLfloat vertices[] = {
		// 位置               // 法向量
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	};

	// 6.1 创建数据对象
	glGenVertexArrays(1, &VAO);	// 生成缓存ID
	glGenBuffers(1, &VBO);		// 生成缓存ID

	// 6.2 绑定数据对象
	// 处理VAO
	glBindVertexArray(VAO);

	// 处理VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 处理EBO
	// ...

	// 6.3 解释顶点数据（数据的：位置、数位、格式，？，步长，偏移量）
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// 法线属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)
		(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// 6.4 解绑 VAO
	glBindVertexArray(0);
}