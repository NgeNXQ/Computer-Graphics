#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include <glut/src/glut.h>
#include <glfw/src/glfw3.h>

GLuint LoadTexture(const char* const);
void DrawCube(const float, const float, const float, GLuint textureID);
void ApplyOrthogonalProjection(const float, const float, const float, const float, const float, const float);

int main(void)
{
	const int VIEWPORT_X_OFFSET = 0;
	const int VIEWPORT_Y_OFFSET = 0;
	const double VIEWPORT_SCALER = 5.0;
	const int VIEWPORT_INITIAL_WIDTH = 1920;
	const int VIEWPORT_INITIAL_HEIGHT = 1080;

	const double CAMERA_FOV = 90.0;
	const double CAMERA_OFFSET_Z = 5.0;
	const double CAMERA_NEAR_CLIPPING_PLANE = 0.01;
	const double CAMERA_FAR_CLIPPING_PLANE = 100.0;

	const double MIN_DELTA_TIME = 0.05;

	const float CUBE_SIDE_LENGTH = 1.0f;
	const float LINE_PROJECTION_WIDTH = 3.0f;
	const float LINE_PROJECTION_LENGTH = 2.5f;

	const float ROTATION_SPEED = 15.0f;
	const float COMPLETE_CIRCLE = 360.0;

	int viewportWidth;
	int viewportHeight;
	double aspectRatio;

	double deltaTime = 0;
	double startTime = 0;

	float rotationAngle = 0.0f;

	if (!glfwInit())
	{
		return EXIT_FAILURE;
	}

	GLFWwindow* const window = glfwCreateWindow(VIEWPORT_INITIAL_WIDTH, VIEWPORT_INITIAL_HEIGHT, "Labwork #7 (7.3). IP-14 Babich Denys", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DOUBLEBUFFER);
	glEnable(GL_COLOR_MATERIAL);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	const GLuint texture = LoadTexture("albedo.bmp");

	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
		aspectRatio = (double)viewportWidth / viewportHeight;
		glViewport(0, 0, viewportWidth, viewportHeight);

		startTime = glfwGetTime();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		#pragma region Top-Left XoY

		glEnable(GL_SCISSOR_TEST);
		glScissor(0, viewportHeight / 2, viewportWidth / 2, viewportHeight / 2);

		ApplyOrthogonalProjection(-aspectRatio * VIEWPORT_SCALER, aspectRatio * VIEWPORT_SCALER, -VIEWPORT_SCALER, VIEWPORT_SCALER, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		gluLookAt(0.0, 0.0, CAMERA_OFFSET_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glTranslatef(-aspectRatio * VIEWPORT_SCALER / 2.0f, VIEWPORT_SCALER / 2.0f, 0.0f);
		glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
		DrawCube(CUBE_SIDE_LENGTH, LINE_PROJECTION_WIDTH, LINE_PROJECTION_LENGTH, texture);
		glPopMatrix();

		glDisable(GL_SCISSOR_TEST);

		#pragma endregion

		#pragma region Top-Right XoZ

		glEnable(GL_SCISSOR_TEST);
		glScissor(viewportWidth / 2, viewportHeight / 2, viewportWidth / 2, viewportHeight / 2);

		ApplyOrthogonalProjection(-aspectRatio * VIEWPORT_SCALER, aspectRatio * VIEWPORT_SCALER, -VIEWPORT_SCALER, VIEWPORT_SCALER, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		gluLookAt(0.0, 0.0, CAMERA_OFFSET_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glTranslatef(aspectRatio * VIEWPORT_SCALER / 2.0f, VIEWPORT_SCALER / 2.0f, 0.0f);
		glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
		DrawCube(CUBE_SIDE_LENGTH, LINE_PROJECTION_WIDTH, LINE_PROJECTION_LENGTH, texture);
		glPopMatrix();

		glDisable(GL_SCISSOR_TEST);

		#pragma endregion

		#pragma region Bottom-Left YoZ

		glEnable(GL_SCISSOR_TEST);
		glScissor(0, 0, viewportWidth / 2, viewportHeight / 2);

		ApplyOrthogonalProjection(-aspectRatio * VIEWPORT_SCALER, aspectRatio * VIEWPORT_SCALER, -VIEWPORT_SCALER, VIEWPORT_SCALER, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		gluLookAt(0.0, 0.0, CAMERA_OFFSET_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glTranslatef(-aspectRatio * VIEWPORT_SCALER / 2.0f, -VIEWPORT_SCALER / 2.0f, 0.0f);
		glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
		DrawCube(CUBE_SIDE_LENGTH, LINE_PROJECTION_WIDTH, LINE_PROJECTION_LENGTH, texture);
		glPopMatrix();

		glDisable(GL_SCISSOR_TEST);

		#pragma endregion

		#pragma region Bottom-Right Isometric

		glEnable(GL_SCISSOR_TEST);
		glScissor(viewportWidth / 2, 0, viewportWidth / 2, viewportHeight / 2);

		ApplyOrthogonalProjection(-aspectRatio * VIEWPORT_SCALER, aspectRatio * VIEWPORT_SCALER, -VIEWPORT_SCALER, VIEWPORT_SCALER, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		gluLookAt(4.5, 4.5, 4.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glTranslatef(aspectRatio * VIEWPORT_SCALER / 2.0f, -VIEWPORT_SCALER / 2.0f, VIEWPORT_SCALER / -2.0f);
		glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);
		DrawCube(CUBE_SIDE_LENGTH, LINE_PROJECTION_WIDTH, LINE_PROJECTION_LENGTH, texture);
		glPopMatrix();

		glDisable(GL_SCISSOR_TEST);

		#pragma endregion

		rotationAngle = fmod(rotationAngle + (ROTATION_SPEED * deltaTime), COMPLETE_CIRCLE);

		deltaTime = glfwGetTime() - startTime;
		deltaTime = deltaTime < MIN_DELTA_TIME ? MIN_DELTA_TIME : deltaTime;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}

GLuint LoadTexture(const char* const filename)
{
	const int DATA_OFFSET = 10;
	const int HEADER_SIZE = 54;
	const int WIDTH_OFFSET = 18;
	const int HEIGHT_OFFSET = 22;
	const int BITS_PER_PIXEL_OFFSET = 28;

	GLuint texture;
	unsigned char* data;
	unsigned short bitsPerPixel;
	unsigned char header[HEADER_SIZE];
	int width, height, dataOffset, imageSize;

	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Failed to open texture file: " << filename << std::endl;
		return 0;
	}

	file.read(reinterpret_cast<char*>(header), HEADER_SIZE);

	if (header[0] != 'B' || header[1] != 'M')
	{
		std::cerr << "Not a BMP file: " << filename << std::endl;
		return 0;
	}

	dataOffset = *reinterpret_cast<int*>(&header[DATA_OFFSET]);
	width = *reinterpret_cast<int*>(&header[WIDTH_OFFSET]);
	height = *reinterpret_cast<int*>(&header[HEIGHT_OFFSET]);
	bitsPerPixel = *reinterpret_cast<short*>(&header[BITS_PER_PIXEL_OFFSET]);

	bool hasAlphaChannel = bitsPerPixel == 32;

	imageSize = width * height * (hasAlphaChannel ? 4 : 3);
	data = new unsigned char[imageSize];

	file.seekg(dataOffset, std::ios::beg);
	file.read(reinterpret_cast<char*>(data), imageSize);
	file.close();

	for (int i = 0; i < imageSize; i += (hasAlphaChannel ? 4 : 3))
	{
		std::swap(data[i], data[i + 2]);
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (hasAlphaChannel)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, hasAlphaChannel ? GL_RGBA : GL_RGB, width, height, 0, hasAlphaChannel ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

	delete[] data;

	return texture;
}

void DrawCube(const float sideLength, const float lineWidth, const float lineLength, GLuint textureID)
{
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBegin(GL_QUADS);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// Front face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-sideLength, -sideLength, sideLength);    // C
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(sideLength, -sideLength, sideLength);     // D
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(sideLength, sideLength, sideLength);      // A
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-sideLength, sideLength, sideLength);     // B

	// Right face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(sideLength, -sideLength, sideLength);     // D
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(sideLength, -sideLength, -sideLength);    // D1
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(sideLength, sideLength, -sideLength);     // A1
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(sideLength, sideLength, sideLength);      // A

	// Back face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-sideLength, -sideLength, -sideLength);   // C1
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(sideLength, -sideLength, -sideLength);    // D1
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(sideLength, sideLength, -sideLength);     // A1
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-sideLength, sideLength, -sideLength);    // B1

	// Left face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-sideLength, -sideLength, -sideLength);   // C1
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-sideLength, -sideLength, sideLength);    // C
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-sideLength, sideLength, sideLength);     // B
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-sideLength, sideLength, -sideLength);    // B1

	// Top face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-sideLength, sideLength, sideLength);     // B
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(sideLength, sideLength, sideLength);      // A
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(sideLength, sideLength, -sideLength);     // A1
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-sideLength, sideLength, -sideLength);    // B1

	// Bottom face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-sideLength, -sideLength, -sideLength);   // C1
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(sideLength, -sideLength, -sideLength);    // D1
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(sideLength, -sideLength, sideLength);     // D
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-sideLength, -sideLength, sideLength);    // C

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glLineWidth(lineWidth);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	glBegin(GL_LINES);

	glVertex3f(sideLength, sideLength, sideLength);
	glVertex3f(lineLength, 0.0f, 0.0f);

	glVertex3f(sideLength, sideLength, sideLength);
	glVertex3f(0.0f, lineLength, 0.0f);

	glVertex3f(sideLength, sideLength, sideLength);
	glVertex3f(0.0f, 0.0f, lineLength);

	glVertex3f(-sideLength, sideLength, sideLength);
	glVertex3f(lineLength, 0.0f, 0.0f);

	glVertex3f(-sideLength, sideLength, sideLength);
	glVertex3f(0.0f, lineLength, 0.0f);

	glVertex3f(-sideLength, sideLength, sideLength);
	glVertex3f(0.0f, 0.0f, lineLength);

	glVertex3f(sideLength, -sideLength, sideLength);
	glVertex3f(lineLength, 0.0f, 0.0f);

	glVertex3f(sideLength, -sideLength, sideLength);
	glVertex3f(0.0f, lineLength, 0.0f);

	glVertex3f(sideLength, -sideLength, sideLength);
	glVertex3f(0.0f, 0.0f, lineLength);

	glVertex3f(sideLength, sideLength, -sideLength);
	glVertex3f(lineLength, 0.0f, 0.0f);

	glVertex3f(sideLength, sideLength, -sideLength);
	glVertex3f(0.0f, lineLength, 0.0f);

	glVertex3f(sideLength, sideLength, -sideLength);
	glVertex3f(0.0f, 0.0f, lineLength);

	glVertex3f(-sideLength, -sideLength, sideLength);
	glVertex3f(lineLength, 0.0f, 0.0f);

	glVertex3f(-sideLength, -sideLength, sideLength);
	glVertex3f(0.0f, lineLength, 0.0f);

	glVertex3f(-sideLength, -sideLength, sideLength);
	glVertex3f(0.0f, 0.0f, lineLength);

	glVertex3f(-sideLength, sideLength, -sideLength);
	glVertex3f(lineLength, 0.0f, 0.0f);

	glVertex3f(-sideLength, sideLength, -sideLength);
	glVertex3f(0.0f, lineLength, 0.0f);

	glVertex3f(-sideLength, sideLength, -sideLength);
	glVertex3f(0.0f, 0.0f, lineLength);

	glVertex3f(sideLength, -sideLength, -sideLength);
	glVertex3f(lineLength, 0.0f, 0.0f);

	glVertex3f(sideLength, -sideLength, -sideLength);
	glVertex3f(0.0f, lineLength, 0.0f);

	glVertex3f(sideLength, -sideLength, -sideLength);
	glVertex3f(0.0f, 0.0f, lineLength);

	glVertex3f(-sideLength, -sideLength, -sideLength);
	glVertex3f(lineLength, 0.0f, 0.0f);

	glVertex3f(-sideLength, -sideLength, -sideLength);
	glVertex3f(0.0f, lineLength, 0.0f);

	glVertex3f(-sideLength, -sideLength, -sideLength);
	glVertex3f(0.0f, 0.0f, lineLength);

	glVertex3f(sideLength, sideLength, sideLength);
	glVertex3f(-lineLength, 0.0f, 0.0f);

	glVertex3f(sideLength, sideLength, sideLength);
	glVertex3f(0.0f, -lineLength, 0.0f);

	glVertex3f(sideLength, sideLength, sideLength);
	glVertex3f(0.0f, 0.0f, -lineLength);

	glVertex3f(-sideLength, sideLength, sideLength);
	glVertex3f(-lineLength, 0.0f, 0.0f);

	glVertex3f(-sideLength, sideLength, sideLength);
	glVertex3f(0.0f, -lineLength, 0.0f);

	glVertex3f(-sideLength, sideLength, sideLength);
	glVertex3f(0.0f, 0.0f, -lineLength);

	glVertex3f(sideLength, -sideLength, sideLength);
	glVertex3f(-lineLength, 0.0f, 0.0f);

	glVertex3f(sideLength, -sideLength, sideLength);
	glVertex3f(0.0f, -lineLength, 0.0f);

	glVertex3f(sideLength, -sideLength, sideLength);
	glVertex3f(0.0f, 0.0f, -lineLength);

	glVertex3f(sideLength, sideLength, -sideLength);
	glVertex3f(-lineLength, 0.0f, 0.0f);

	glVertex3f(sideLength, sideLength, -sideLength);
	glVertex3f(0.0f, -lineLength, 0.0f);

	glVertex3f(sideLength, sideLength, -sideLength);
	glVertex3f(0.0f, 0.0f, -lineLength);

	glVertex3f(-sideLength, -sideLength, sideLength);
	glVertex3f(-lineLength, 0.0f, 0.0f);

	glVertex3f(-sideLength, -sideLength, sideLength);
	glVertex3f(0.0f, -lineLength, 0.0f);

	glVertex3f(-sideLength, -sideLength, sideLength);
	glVertex3f(0.0f, 0.0f, -lineLength);

	glVertex3f(-sideLength, sideLength, -sideLength);
	glVertex3f(-lineLength, 0.0f, 0.0f);

	glVertex3f(-sideLength, sideLength, -sideLength);
	glVertex3f(0.0f, -lineLength, 0.0f);

	glVertex3f(-sideLength, sideLength, -sideLength);
	glVertex3f(0.0f, 0.0f, -lineLength);

	glVertex3f(sideLength, -sideLength, -sideLength);
	glVertex3f(-lineLength, 0.0f, 0.0f);

	glVertex3f(sideLength, -sideLength, -sideLength);
	glVertex3f(0.0f, -lineLength, 0.0f);

	glVertex3f(sideLength, -sideLength, -sideLength);
	glVertex3f(0.0f, 0.0f, -lineLength);

	glVertex3f(-sideLength, -sideLength, -sideLength);
	glVertex3f(-lineLength, 0.0f, 0.0f);

	glVertex3f(-sideLength, -sideLength, -sideLength);
	glVertex3f(0.0f, -lineLength, 0.0f);

	glVertex3f(-sideLength, -sideLength, -sideLength);
	glVertex3f(0.0f, 0.0f, -lineLength);

	glEnd();

	glFlush();
}

void ApplyOrthogonalProjection(const float left, const float right, const float bottom, const float top, const float nearPlane, const float farPlane)
{
	float matrix[16];
	float tx = -(right + left) / (right - left);
	float ty = -(top + bottom) / (top - bottom);
	float tz = -(farPlane + nearPlane) / (farPlane - nearPlane);

	matrix[0] = 2.0f / (right - left);
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = 2.0f / (top - bottom);
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = -2.0f / (farPlane - nearPlane);
	matrix[11] = 0.0f;

	matrix[12] = tx;
	matrix[13] = ty;
	matrix[14] = tz;
	matrix[15] = 1.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(matrix);
}