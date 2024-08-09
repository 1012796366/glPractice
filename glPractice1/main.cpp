#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, 800, 600);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

GLfloat verticles[] = {
	// 位置				// 颜色
 	 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 	// ↗
	 0.5f, -0.5f, 0.0f,	 0.0f, 0.5f, 1.0f,	// ↘
	-0.5f, -0.5f, 0.0f,	 0.0f, 0.0f, 1.0f,	// ↙
	-0.5f,  0.5f, 0.0f,	 0.0f, 1.0f, 0.5f,	// ↖
};

int indices[] = {
	0, 1, 3,
	1, 2, 3
};

char const* vshadersrc =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 customColor;\n"
"void main() {\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"	customColor = aColor;\n"	
"}\0";

char const* fshadersrc =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 customColor;\n"
"void main() {\n"
"	FragColor = vec4(customColor, 1.0);\n"
"}\0";

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "glPractice1", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Error creating window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "error init glad" << std::endl;
		glfwTerminate();
		return -1;
	}

	unsigned int vshader;
	vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vshadersrc, nullptr);
	glCompileShader(vshader);
	int success;
	char infoLog[512];
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vshader, 512, nullptr, infoLog);
		std::cerr << "vshader err:" << infoLog << std::endl;
	}

	unsigned int fshader;
	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fshadersrc, nullptr);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fshader, 512, nullptr, infoLog);
		std::cerr << "fshader err:" << infoLog << std::endl;
	}

	unsigned int pshader;
	pshader = glCreateProgram();
	glAttachShader(pshader, vshader);
	glAttachShader(pshader, fshader);
	glLinkProgram(pshader);
	glGetProgramiv(pshader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(pshader, 512, nullptr, infoLog);
		std::cerr << "link err:" << infoLog << std::endl;
	}

	unsigned int vao, vbo, ebo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);
	// 绑定 VAO
	glBindVertexArray(vao);

	// 绑定 VBO 并向其中存入顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

	// 绑定 EBO 并向其中存入序列数据
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 介绍存入的数据的属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	
	glDeleteShader(vshader);
	glDeleteShader(fshader);

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLdouble timeValue = glfwGetTime();
		GLdouble greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(pshader, "customColor");
		glUseProgram(pshader);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glBindVertexArray(0);
	glDeleteBuffers(1, &vao);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glUseProgram(0);
	glfwTerminate();
	return 0;
}