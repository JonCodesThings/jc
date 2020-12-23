#include <glad.h>

#define NULL 0

GLint vertexShaderID, fragmentShaderID, program;
GLint vertexBufferID, indexBufferID;

void glInit()
{
	gladLoadGL();

	const char *vertexShaderSource = "attribute vec3 position; void main(void) { gl_Position = vec4(position, 1.0); }";
	const char *fragmentShaderSource = "void main(void) { gl_FragColor[0] = 1.0; gl_FragColor[1] = 0.0; gl_FragColor[2] = 1.0; }";

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShaderID);

	glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderID);

	program = glCreateProgram();
	glAttachShader(program, vertexShaderID);
	glAttachShader(program, fragmentShaderID);
	glLinkProgram(program);

	glUseProgram(program);

	glBindAttribLocation(program, 0, "position");

	float vertices[] =
	{
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	unsigned int indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	//Generate the buffers
	glGenBuffers(1, &vertexBufferID);
	glGenBuffers(1, &indexBufferID);

	//Copy the vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);

	//Copy the index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 6, indices, GL_STATIC_DRAW);
}

void clear_render_target()
{
	glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void draw_triangle()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(0);
}

void glShutdown()
{
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(program);
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &indexBufferID);
}