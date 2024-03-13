#include <cmath>
#include <cstdlib>

#include <glut/src/glut.h>
#include <glfw/src/glfw3.h>

void DrawCube(const float);

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

    GLFWwindow* const window = glfwCreateWindow(VIEWPORT_INITIAL_WIDTH, VIEWPORT_INITIAL_HEIGHT, "Labwork #3 (3.1). IP-14 Babich Denys", NULL, NULL);

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

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

        glClearColor(0.15f, 0.53f, 0.53f, 1.0f);

        glPushMatrix();

        glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);

        rotationAngle = fmod(rotationAngle + (ROTATION_SPEED * deltaTime), COMPLETE_CIRCLE);

        DrawCube(CUBE_SIDE_LENGTH);

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

void DrawCube(const float sideLength)
{
    glBegin(GL_QUADS);

    // Front face (бузковий)
    glColor4f(0.8f, 0.6f, 0.8f, 1.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(sideLength, sideLength, sideLength);      // A
    glVertex3f(-sideLength, sideLength, sideLength);     // B
    glVertex3f(-sideLength, -sideLength, sideLength);    // C
    glVertex3f(sideLength, -sideLength, sideLength);     // D

    // Right face (лимонний)
    glColor4f(1.0f, 1.0f, 0.4f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(sideLength, sideLength, -sideLength);     // A1
    glVertex3f(sideLength, sideLength, sideLength);      // A
    glVertex3f(sideLength, -sideLength, sideLength);     // D
    glVertex3f(sideLength, -sideLength, -sideLength);    // D1

    // Back face (коричневий)
    glColor4f(0.0f, 0.5f, 0.8f, 1.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-sideLength, sideLength, -sideLength);    // B1
    glVertex3f(sideLength, sideLength, -sideLength);     // A1
    glVertex3f(sideLength, -sideLength, -sideLength);    // D1
    glVertex3f(-sideLength, -sideLength, -sideLength);   // C1

    // Left face (морська хвиля)
    glColor4f(0.8f, 0.0f, 0.2f, 1.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-sideLength, sideLength, sideLength);     // B
    glVertex3f(-sideLength, sideLength, -sideLength);    // B1
    glVertex3f(-sideLength, -sideLength, -sideLength);   // B1
    glVertex3f(-sideLength, -sideLength, sideLength);    // C

    // Top face (вишневий)
    glColor4f(0.3f, 0.2f, 0.1f, 1.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(sideLength, sideLength, -sideLength);     // A1
    glVertex3f(-sideLength, sideLength, -sideLength);    // B1
    glVertex3f(-sideLength, sideLength, sideLength);     // B
    glVertex3f(sideLength, sideLength, sideLength);      // A

    // Bottom face (салатовий)
    glColor4f(0.0f, 0.8f, 0.4f, 1.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(sideLength, -sideLength, sideLength);     // D
    glVertex3f(-sideLength, -sideLength, sideLength);    // C
    glVertex3f(-sideLength, -sideLength, -sideLength);   // C1
    glVertex3f(sideLength, -sideLength, -sideLength);    // D1

    glEnd();
}