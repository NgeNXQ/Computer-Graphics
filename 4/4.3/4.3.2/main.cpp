#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include <glut/src/glut.h>
#include <glfw/src/glfw3.h>

void DrawCube(const float, GLuint);
GLuint LoadTexture(const char* const);

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
    const float CUBE_TEXTURE_TILING = 1.5f;

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

    GLFWwindow* const window = glfwCreateWindow(VIEWPORT_INITIAL_WIDTH, VIEWPORT_INITIAL_HEIGHT, "Labwork #4 (4.3.2). IP-14 Babich Denys", NULL, NULL);

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

    const GLuint texture = LoadTexture("TextureAlbedo.bmp");

    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);

        aspectRatio = (double)viewportWidth / viewportHeight;

        glViewport(VIEWPORT_X_OFFSET, VIEWPORT_Y_OFFSET, viewportWidth, viewportHeight);

        startTime = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        //gluPerspective(CAMERA_FOV, (double)aspectRatio, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);
        glOrtho(-VIEWPORT_SCALER * aspectRatio, VIEWPORT_SCALER * aspectRatio, -VIEWPORT_SCALER, VIEWPORT_SCALER, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);
        gluLookAt(0.0, 0.0, CAMERA_OFFSET_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        glMatrixMode(GL_TEXTURE);

        glLoadIdentity();

        glScalef(CUBE_TEXTURE_TILING, CUBE_TEXTURE_TILING, CUBE_TEXTURE_TILING);

        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        glClearColor(0.969f, 0.663f, 0.847f, 1.0f);

        glPushMatrix();

        glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);

        rotationAngle = fmod(rotationAngle + (ROTATION_SPEED * deltaTime), COMPLETE_CIRCLE);

        DrawCube(CUBE_SIDE_LENGTH, texture);

        glPopMatrix();

        deltaTime = glfwGetTime() - startTime;
        deltaTime = deltaTime < MIN_DELTA_TIME ? MIN_DELTA_TIME : deltaTime;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    glDeleteTextures(1, &texture);

    return EXIT_SUCCESS;
}

void DrawCube(const float sideLength, GLuint textureID)
{
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);

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
}

GLuint LoadTexture(const char* const filename)
{
    const int HEADER_OFFSET = 54;
    const int COLOR_CHANNELS_COUNT = 4;

    const int FILE_PAYLOAD_OFFSET = 0x0A;
    const int FILE_TEXTURE_SIZE_OFFSET = 0x22;
    const int FILE_TEXTURE_WIDTH_OFFSET = 0x12;
    const int FILE_TEXTURE_HEIGHT_OFFSET = 0x16;

    GLuint texture;

    unsigned char fileHeader[HEADER_OFFSET];

    int width, height;
    int fileTextureSize, filePayloadPosition;

    unsigned char* textureColorChannels;

    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Failed to open texture file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    if (!file.read(reinterpret_cast<char*>(fileHeader), HEADER_OFFSET) || (fileHeader[0] != 'B' || fileHeader[1] != 'M'))
    {
        std::cerr << "Not a BMP file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    filePayloadPosition = *(int*)&(fileHeader[FILE_PAYLOAD_OFFSET]);
    fileTextureSize = *(int*)&(fileHeader[FILE_TEXTURE_SIZE_OFFSET]);

    width = *(int*)&(fileHeader[FILE_TEXTURE_WIDTH_OFFSET]);
    height = *(int*)&(fileHeader[FILE_TEXTURE_HEIGHT_OFFSET]);

    textureColorChannels = new unsigned char[fileTextureSize];

    file.seekg(filePayloadPosition);
    file.read(reinterpret_cast<char*>(textureColorChannels), fileTextureSize);
    file.close();

    for (int i = 0; i < fileTextureSize; i += COLOR_CHANNELS_COUNT)
    {
        std::swap(textureColorChannels[i], textureColorChannels[i + 2]);
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureColorChannels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete[] textureColorChannels;

    return texture;
}
