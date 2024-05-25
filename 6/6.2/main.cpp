#include <cmath>
#include <string>
#include <cstdlib>

#include <glut/src/glut.h>
#include <glfw/src/glfw3.h>

int main(int argc, char **argv)
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

    const double TEAPOT_SIZE = 1.25;

    const float ROTATION_SPEED = 15.0f;
    const float COMPLETE_CIRCLE = 360.0;

    int viewportWidth;
    int viewportHeight;
    double aspectRatio;

    double deltaTime = 0;
    double startTime = 0;

    float rotationAngle = 0.0f;

    glutInit(&argc, argv);

    if (!glfwInit())
    {
        return EXIT_FAILURE;
    }

    GLFWwindow* const window = glfwCreateWindow(VIEWPORT_INITIAL_WIDTH, VIEWPORT_INITIAL_HEIGHT, "Labwork #6 (6.2). IP-14 Babich Denys", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DOUBLEBUFFER);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);

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
        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
        glutSolidTeapot(TEAPOT_SIZE);
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
        glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
        glutSolidTeapot(TEAPOT_SIZE);
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
        glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
        glutSolidTeapot(TEAPOT_SIZE);
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
        glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
        glutSolidTeapot(TEAPOT_SIZE);
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