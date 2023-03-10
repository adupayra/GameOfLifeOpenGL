#pragma once
#include <glad/glad.h>
#include <glfw3.h>

class WindowManager
{
private:
	GLFWwindow* m_wind;
	int m_width;
	int m_height;

	void loadGlad();
public:
	WindowManager(int, int, const char*);

	WindowManager() = default;

	~WindowManager();

	GLFWwindow* getWindow() { return m_wind; }

	int getWidth() { return m_width; }

	int getHeight() { return m_height; }

	static void glfwErrorCallback(int, const char*);

	static void glfwKeyCallback(GLFWwindow*, int, int, int, int);

	static void glfwFrameBuffersizeCallback(GLFWwindow*, int, int);

	void update();

	void processEvents();

	void show();

	bool isClosedState();

};

