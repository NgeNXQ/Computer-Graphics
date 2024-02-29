#include <cmath>
#include <cstdlib>

#include <glut/src/glut.h>
#include <glfw/src/glfw3.h>

#define _USE_MATH_DEFINES

#include <math.h>

void DrawPyramid(const int, const float, const float);

int main(void)
{
    const int VIEWPORT_X_OFFSET = 0;
    const int VIEWPORT_Y_OFFSET = 0;
    const double VIEWPORT_SCALER = 7.5;
    const int VIEWPORT_INITIAL_WIDTH = 1920;
    const int VIEWPORT_INITIAL_HEIGHT = 1080;

    const double CAMERA_FOV = 90.0;
    const double CAMERA_OFFSET_Z = 5.0;
    const double CAMERA_NEAR_CLIPPING_PLANE = 0.01;
    const double CAMERA_FAR_CLIPPING_PLANE = 100.0;

    const double MIN_DELTA_TIME = 0.05;

    const int PYRAMID_SIDES_COUNT = 5;
    const float PYRAMID_HEIGHT = 5.0f;
    const float PYRAMID_RADIUS_CIRCUMCIRCLE_BASE = 5.0f;

    const float ROTATION_SPEED = 25.0f;
    const float COMPLETE_CIRCLE = 360.0f;

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

    GLFWwindow* const window = glfwCreateWindow(VIEWPORT_INITIAL_WIDTH, VIEWPORT_INITIAL_HEIGHT, "Labwork #2 (2.1). IP-14 Babich Denys", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DOUBLEBUFFER);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);

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

        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        glClearColor(0.525f, 0.835f, 0.969f, 1.0f);

        glPushMatrix();

        glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);

        rotationAngle = fmod(rotationAngle + (ROTATION_SPEED * deltaTime), COMPLETE_CIRCLE);

        DrawPyramid(PYRAMID_SIDES_COUNT, PYRAMID_HEIGHT, PYRAMID_RADIUS_CIRCUMCIRCLE_BASE);

        glPopMatrix();

        deltaTime = glfwGetTime() - startTime;
        deltaTime = deltaTime < MIN_DELTA_TIME ? MIN_DELTA_TIME : deltaTime;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}

void DrawPyramid(const int sidesCount, const float height, const float radiusCircumcircleBase)
{
    const float DELTA_FI = 2.0f * M_PI / sidesCount;

    float fi = 0.0f;

    glBegin(GL_TRIANGLES);

    for (int i = 1; i <= sidesCount; ++i)
    {
        glColor4f(static_cast<float>(i % 2), static_cast<float>((i % 3) / 2.0), static_cast<float>((i % 5) / 4.0), 1.0f);

        float normalX = cos(fi + DELTA_FI / 2.0f) * sin(atan(height / radiusCircumcircleBase));
        float normalY = sin(fi + DELTA_FI / 2.0f) * sin(atan(height / radiusCircumcircleBase));
        float normalZ = cos(atan(height / radiusCircumcircleBase));

        glNormal3f(normalX, normalY, normalZ);

        glVertex3f(0.0f, 0.0f, height);
        glVertex3f(radiusCircumcircleBase * cos(fi), radiusCircumcircleBase * sin(fi), 0.0f);
        glVertex3f(radiusCircumcircleBase * cos(fi + DELTA_FI), radiusCircumcircleBase * sin(fi + DELTA_FI), 0.0f);

        fi += DELTA_FI;
    }

    glEnd();

    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, -1.0f);

    glColor4f(1.0f, 0.0f, 0.6f, 1.0f);

    for (int i = 0; i < sidesCount; ++i)
    {
        glVertex3f(radiusCircumcircleBase * cos(fi), radiusCircumcircleBase * sin(fi), 0.0f);
        fi += DELTA_FI;
    }

    glEnd();
}