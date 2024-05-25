#include <cmath>
#include <string>
#include <cstdlib>

#include <glut/src/glut.h>
#include <glfw/src/glfw3.h>

void DrawCube(const float);

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

    const float CUBE_SIDE_LENGTH = 1.25f;

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

    GLFWwindow* const window = glfwCreateWindow(VIEWPORT_INITIAL_WIDTH, VIEWPORT_INITIAL_HEIGHT, "Labwork #6 (6.1). IP-14 Babich Denys", NULL, NULL);

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

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-aspectRatio * VIEWPORT_SCALER, aspectRatio * VIEWPORT_SCALER, -VIEWPORT_SCALER, VIEWPORT_SCALER, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        gluLookAt(0.0, 0.0, CAMERA_OFFSET_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glTranslatef(-aspectRatio * VIEWPORT_SCALER / 2.0f, VIEWPORT_SCALER / 2.0f, 0.0f);
        glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
        DrawCube(CUBE_SIDE_LENGTH);
        glPopMatrix();

        glDisable(GL_SCISSOR_TEST);

        #pragma endregion

        #pragma region Top-Right XoZ

        glEnable(GL_SCISSOR_TEST);
        glScissor(viewportWidth / 2, viewportHeight / 2, viewportWidth / 2, viewportHeight / 2);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-aspectRatio * VIEWPORT_SCALER, aspectRatio * VIEWPORT_SCALER, -VIEWPORT_SCALER, VIEWPORT_SCALER, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        gluLookAt(0.0, 0.0, CAMERA_OFFSET_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glTranslatef(aspectRatio * VIEWPORT_SCALER / 2.0f, VIEWPORT_SCALER / 2.0f, 0.0f);
        glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
        DrawCube(CUBE_SIDE_LENGTH);
        glPopMatrix();

        glDisable(GL_SCISSOR_TEST);

        #pragma endregion

        #pragma region Bottom-Left YoZ

        glEnable(GL_SCISSOR_TEST);
        glScissor(0, 0, viewportWidth / 2, viewportHeight / 2);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-aspectRatio * VIEWPORT_SCALER, aspectRatio * VIEWPORT_SCALER, -VIEWPORT_SCALER, VIEWPORT_SCALER, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        gluLookAt(0.0, 0.0, CAMERA_OFFSET_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glTranslatef(-aspectRatio * VIEWPORT_SCALER / 2.0f, -VIEWPORT_SCALER / 2.0f, 0.0f);
        glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
        DrawCube(CUBE_SIDE_LENGTH);
        glPopMatrix();

        glDisable(GL_SCISSOR_TEST);

        #pragma endregion

        #pragma region Bottom-Right Isometric

        glEnable(GL_SCISSOR_TEST);
        glScissor(viewportWidth / 2, 0, viewportWidth / 2, viewportHeight / 2);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-aspectRatio * VIEWPORT_SCALER, aspectRatio * VIEWPORT_SCALER, -VIEWPORT_SCALER, VIEWPORT_SCALER, CAMERA_NEAR_CLIPPING_PLANE, CAMERA_FAR_CLIPPING_PLANE);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        gluLookAt(4.5, 4.5, 4.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glTranslatef(aspectRatio * VIEWPORT_SCALER / 2.0f, -VIEWPORT_SCALER / 2.0f, VIEWPORT_SCALER / -2.0f);
        glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);
        DrawCube(CUBE_SIDE_LENGTH);
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

void DrawCube(const float sideLength)
{
    glBegin(GL_QUADS);

    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

    // Front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(sideLength, sideLength, sideLength);      // A
    glVertex3f(-sideLength, sideLength, sideLength);     // B
    glVertex3f(-sideLength, -sideLength, sideLength);    // C
    glVertex3f(sideLength, -sideLength, sideLength);     // D

    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(sideLength, sideLength, -sideLength);     // A1
    glVertex3f(sideLength, sideLength, sideLength);      // A
    glVertex3f(sideLength, -sideLength, sideLength);     // D
    glVertex3f(sideLength, -sideLength, -sideLength);    // D1

    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-sideLength, sideLength, -sideLength);    // B1
    glVertex3f(sideLength, sideLength, -sideLength);     // A1
    glVertex3f(sideLength, -sideLength, -sideLength);    // D1
    glVertex3f(-sideLength, -sideLength, -sideLength);   // C1

    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-sideLength, sideLength, sideLength);     // B
    glVertex3f(-sideLength, sideLength, -sideLength);    // B1
    glVertex3f(-sideLength, -sideLength, -sideLength);   // B1
    glVertex3f(-sideLength, -sideLength, sideLength);    // C

    glColor4f(0.0f, 1.0f, 1.0f, 1.0f);

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(sideLength, sideLength, -sideLength);     // A1
    glVertex3f(-sideLength, sideLength, -sideLength);    // B1
    glVertex3f(-sideLength, sideLength, sideLength);     // B
    glVertex3f(sideLength, sideLength, sideLength);      // A

    glColor4f(1.0f, 0.0f, 1.0f, 1.0f);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(sideLength, -sideLength, sideLength);     // D
    glVertex3f(-sideLength, -sideLength, sideLength);    // C
    glVertex3f(-sideLength, -sideLength, -sideLength);   // C1
    glVertex3f(sideLength, -sideLength, -sideLength);    // D1

    glEnd();
}