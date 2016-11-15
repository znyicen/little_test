#pragma once
// ## ע������ ##
// 1. ��filesystem.h���޸ģ�
//    #include "root_directory.h" - ԭ���Ĵ���
//    const char* logl_root = "C:/LearnOpenGL-master"; // �趨��Ŀ¼
// 2. ��Ҫ�رչ��̵� C/C++ SDL��� ����
// 3. �Թ�������SOIL.lib
// ## ע������ ##

//// I ��ͷ ////
#include <iostream>
#include <cmath>

// GLEW
// GLEW ���Զ�ʶ�����ƽ̨��֧�ֵ�ȫ��OpenGL�߼���չ����
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
// OpenGL ���ڹ����ֱ����л������̡�����Լ���Ϸ�ֱ�����ʱ�����롢�̴߳����ȵȡ�
#include <GLFW/glfw3.h>

// Other Libs
// ͼ���ȡ��
#include <SOIL.h>
// GLM ��ѧ��
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include <learnopengl/shader.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/Camera.h>


//// II ����ԭ�� ////
// opengl��ʼ��
void openGL_setup();
// ��������ص�����
void key_callback(GLFWwindow* window, int key, int scancode,
	int action, int mode);
// �������ص�����
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// �������ص�����
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// ���������
void do_movement();


//// III ȫ�ֱ��� ////
// ���ڳߴ�
const GLuint WIDTH =800, HEIGHT = 600;

// ��Ӱ������
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];

// �ƹ�����
glm::vec3 lightPos(1.2f, 0.5f, 2.0f);

// ֡��ʱ
GLfloat deltaTime = 0.0f; // ��ǰ֡����һ֡����ʱ��
GLfloat lastFrame = 0.0f; // ��һ֡
// �������ڶ���
GLFWwindow* window;

//// V ����ʵ�� ////
// opengl��ʼ��ʵ��
void openGL_setup() {
	std::cout << "����GLFW����, OpenGL�汾��3.3��" << std::endl;
	// 1.0 ��ʼ��GLFW
	glfwInit();
	// 1.1 �趨GLFW�������ģʽ
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	// 2.0 ʵ��������
	window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	// 2.1 �����ڼ���openGL����
	glfwMakeContextCurrent(window);

	// ��������Ļص����� 
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// 3.0 ��ʼ��GLEW
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ����ʾ���
	glewExperimental = GL_TRUE;                                  // ʹ���ִ�������
	glewInit();

	// 4.0 �����ӿ�
	glViewport(0, 0, WIDTH, HEIGHT);

	// OpenGL options
	// ������Ȳ���
	glEnable(GL_DEPTH_TEST);

	// ���û���ģʽ
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // �߿�ģʽ
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Ĭ�����ģʽ
}

// ����ص�����ʵ��
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// ��λ״̬��¼(��ס������һ���������֧�ֶ��λͬ�´���
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

// ��λ״̬����
void do_movement()
{
	// ���������
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

	GLfloat sensitivity = 0.05; // ���������
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}