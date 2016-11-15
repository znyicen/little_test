#pragma once
// ## 注意事项 ##
// 1. 对filesystem.h的修改：
//    #include "root_directory.h" - 原本的代码
//    const char* logl_root = "C:/LearnOpenGL-master"; // 设定根目录
// 2. 需要关闭工程的 C/C++ SDL检查 特性
// 3. 对工程连接SOIL.lib
// ## 注意事项 ##

//// I 库头 ////
#include <iostream>
#include <cmath>

// GLEW
// GLEW 能自动识别你的平台所支持的全部OpenGL高级扩展涵数
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
// OpenGL 窗口管理、分辨率切换、键盘、鼠标以及游戏手柄、定时器输入、线程创建等等。
#include <GLFW/glfw3.h>

// Other Libs
// 图像读取库
#include <SOIL.h>
// GLM 数学库
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include <learnopengl/shader.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/Camera.h>


//// II 函数原型 ////
// opengl初始化
void openGL_setup();
// 键盘输入回调函数
void key_callback(GLFWwindow* window, int key, int scancode,
	int action, int mode);
// 鼠标输入回调函数
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// 鼠标滚动回调函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// 输出入理函数
void do_movement();


//// III 全局变量 ////
// 窗口尺寸
const GLuint WIDTH =800, HEIGHT = 600;

// 摄影机变量
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];

// 灯光属性
glm::vec3 lightPos(1.2f, 0.5f, 2.0f);

// 帧耗时
GLfloat deltaTime = 0.0f; // 当前帧到上一帧所耗时间
GLfloat lastFrame = 0.0f; // 上一帧
// 创建窗口对象
GLFWwindow* window;

//// V 函数实现 ////
// opengl初始化实现
void openGL_setup() {
	std::cout << "进入GLFW环境, OpenGL版本：3.3。" << std::endl;
	// 1.0 初始化GLFW
	glfwInit();
	// 1.1 设定GLFW程序基本模式
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	// 2.0 实例化窗口
	window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	// 2.1 将窗口加入openGL环境
	glfwMakeContextCurrent(window);

	// 设置所需的回调函数 
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// 3.0 初始化GLEW
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 不显示光标
	glewExperimental = GL_TRUE;                                  // 使用现代化技术
	glewInit();

	// 4.0 设置视口
	glViewport(0, 0, WIDTH, HEIGHT);

	// OpenGL options
	// 开启深度测试
	glEnable(GL_DEPTH_TEST);

	// 设置绘制模式
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 线框模式
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 默认填充模式
}

// 输入回调函数实现
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// 键位状态记录(待住函数中一并处理，则可支持多键位同事处理）
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

// 键位状态处理
void do_movement()
{
	// 摄像机控制
	GLfloat cameraSpeed = 5.0f * deltaTime;
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05; // 鼠标灵敏度
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}