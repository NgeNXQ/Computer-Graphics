#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include <glut/src/glut.h>
#include <glfw/src/glfw3.h>

GLuint LoadTexture(const char* const);
void DrawCube(const float, const GLuint*);

int main(void)
{
    const int VIEWPORT_X_OFFSET = 0;
    const int VIEWPORT_Y_OFFSET = 0;
    const double VIEWPORT_SCALER = 3.0;
    const int VIEWPORT_INITIAL_WIDTH = 1920;
    const int VIEWPORT_INITIAL_HEIGHT = 1080;

    const double CAMERA_FOV = 90.0;
    const double CAMERA_OFFSET_Z = 5.0;
    const double CAMERA_NEAR_CLIPPING_PLANE = 0.01;
    const double CAMERA_FAR_CLIPPING_PLANE = 100.0;

    const double MIN_DELTA_TIME = 0.05;

    const float CUBE_SIDE_LENGTH = 1.5f;

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

    GLFWwindow* const window = glfwCreateWindow(VIEWPORT_INITIAL_WIDTH, VIEWPORT_INITIAL_HEIGHT, "Labwork #5 (5.3). IP-14 Babich Denys", NULL, NULL);

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

    std::vector<GLuint> textures;

    textures.push_back(LoadTexture("1.bmp"));
    textures.push_back(LoadTexture("2.bmp"));
    textures.push_back(LoadTexture("3.bmp"));
    textures.push_back(LoadTexture("4.bmp"));
    textures.push_back(LoadTexture("5.bmp"));
    textures.push_back(LoadTexture("6.bmp"));

    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);

        aspectRatio = (double)viewportWidth / viewportHeight;

        glViewport(VIEWPORT_X_OFFSET, VIEWPORT_Y_OFFSET, viewportWidth, viewportHeight);

        startTime = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        glOrtho(-VIEWPORT_SCALER * aspectRatio, VIEWPORT_SCALER * aspectRatio, -VIEWPORT_SCALER, VIEWPORT_SCALER, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);
        gluLookAt(0.0, 0.0, CAMERA_OFFSET_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        glClearColor(0.15f, 0.53f, 0.53f, 1.0f);

        glPushMatrix();

        glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);

        rotationAngle = fmod(rotationAngle + (ROTATION_SPEED * deltaTime), COMPLETE_CIRCLE);

        DrawCube(CUBE_SIDE_LENGTH, textures.data());

        glPopMatrix();

        deltaTime = glfwGetTime() - startTime;
        deltaTime = deltaTime < MIN_DELTA_TIME ? MIN_DELTA_TIME : deltaTime;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    for (GLuint texture : textures)
    {
        glDeleteTextures(1, &texture);
    }

    return EXIT_SUCCESS;
}

void DrawCube(const float sideLength, const GLuint* textures)
{
    // Front face
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-sideLength, -sideLength, sideLength);    // C
    glTexCoord2f(1.0f, 0.0f); glVertex3f(sideLength, -sideLength, sideLength);     // D
    glTexCoord2f(1.0f, 1.0f); glVertex3f(sideLength, sideLength, sideLength);      // A
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-sideLength, sideLength, sideLength);     // B
    glEnd();

    // Right face
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(sideLength, -sideLength, sideLength);     // D
    glTexCoord2f(1.0f, 0.0f); glVertex3f(sideLength, -sideLength, -sideLength);    // D1
    glTexCoord2f(1.0f, 1.0f); glVertex3f(sideLength, sideLength, -sideLength);     // A1
    glTexCoord2f(0.0f, 1.0f); glVertex3f(sideLength, sideLength, sideLength);      // A
    glEnd();

    // Back face
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-sideLength, -sideLength, -sideLength);   // C1
    glTexCoord2f(1.0f, 0.0f); glVertex3f(sideLength, -sideLength, -sideLength);    // D1
    glTexCoord2f(1.0f, 1.0f); glVertex3f(sideLength, sideLength, -sideLength);     // A1
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-sideLength, sideLength, -sideLength);    // B1
    glEnd();

    // Left face
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-sideLength, -sideLength, -sideLength);   // C1
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-sideLength, -sideLength, sideLength);    // C
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-sideLength, sideLength, sideLength);     // B
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-sideLength, sideLength, -sideLength);    // B1
    glEnd();

    // Top face
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-sideLength, sideLength, sideLength);     // B
    glTexCoord2f(1.0f, 0.0f); glVertex3f(sideLength, sideLength, sideLength);      // A
    glTexCoord2f(1.0f, 1.0f); glVertex3f(sideLength, sideLength, -sideLength);     // A1
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-sideLength, sideLength, -sideLength);    // B1
    glEnd();

    // Bottom face
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-sideLength, -sideLength, -sideLength);   // C1
    glTexCoord2f(1.0f, 0.0f); glVertex3f(sideLength, -sideLength, -sideLength);    // D1
    glTexCoord2f(1.0f, 1.0f); glVertex3f(sideLength, -sideLength, sideLength);     // D
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-sideLength, -sideLength, sideLength);    // C
    glEnd();
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

    if (bitsPerPixel != 24)
    {
        std::cerr << "Only 24-bit BMP files are supported: " << filename << std::endl;
        return 0;
    }

    imageSize = width * height * 3;
    data = new unsigned char[imageSize];

    file.seekg(dataOffset, std::ios::beg);
    file.read(reinterpret_cast<char*>(data), imageSize);
    file.close();

    for (int i = 0; i < imageSize; i += 3)
    {
        std::swap(data[i], data[i + 2]);
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    delete[] data;

    return texture;
}
