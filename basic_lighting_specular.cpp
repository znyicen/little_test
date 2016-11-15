// CK_head.h ：
// 库头引用
// 函数原型及实现
// 全局变量
#include "CK_head.h"

// 创建顶点缓存对象，顶点数组对象
GLuint VBO, VAO;

GLfloat pi = 3.1415926;
GLfloat degToRad(GLfloat degree) {
	GLfloat radian = degree * pi / 180.0;
	return radian;
}

void setVerts() {
	// 6.0 设置顶点数据
	GLfloat r = 0.5f;
	
	GLfloat vertices[] = {
		// 位置				// color
		 sin(degToRad(  0.0))*r, cos(degToRad(  0.0))*r, 0.0,	1.0, 0.0, 0.0,
		 sin(degToRad(120.0))*r, cos(degToRad(120.0))*r, 0.0,	0.0, 1.0, 0.0,
		 sin(degToRad(240.0))*r, cos(degToRad(240.0))*r, 0.0,	0.0, 0.0, 1.0
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
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// 6.4 解绑 VAO
	glBindVertexArray(0);
}

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

		// 获取unifrom的地址
		// ...
											
		// 7.32 使用纹理单元绑定纹理
		// ...

		// 7.33 激活渲染器
		surfaceShader.Use();

		// 更新unifrom的值（必须激活着色器）
		// ...

		// 创建变换
		glm::mat4 transform; // 4*4单位矩阵

		// 旋转矩阵
		transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 1.0f, glm::vec3(0.0f, 0.0f, -1.0f));

		// 平移矩阵（先平移到中心点，然后旋转）
		//transform = glm::translate(transform, glm::vec3(0.0f, 0.15f, 0.0f));

		// 请求uniform变量的地址
		GLint transformLoc = glGetUniformLocation(surfaceShader.Program, "transform");
		// 把矩阵传递给着色器 
		// 参数1：uniform的地址(Location)
		// 参数2：将要发送多少个矩阵，目前是1
		// 参数3：询问我们我们是否希望对我们的矩阵进行置换(Transpose)，也就是说交换我们矩阵的行和列。
		// OpenGL开发者通常使用一种内部矩阵布局叫做以列为主顺序的(Column-major Ordering)布局。
		// GLM已经是用以列为主顺序定义了它的矩阵，所以并不需要置换矩阵，我们填GL_FALSE。
		// 参数4：是实际的矩阵数据，但是GLM并不是把它们的矩阵储存为OpenGL所希望的那种，
		// 因此我们要先用GLM的自带的函数value_ptr来变换这些数据。
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// 7.35 开始绘制
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// 交换屏幕缓冲区
		glfwSwapBuffers(window);
	}
	// 8.0 释放资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;

}

