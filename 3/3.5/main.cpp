#include <cmath>
#include <cstdlib>

#include <glut/src/glut.h>
#include <glfw/src/glfw3.h>

#define _USE_MATH_DEFINES

#include <math.h>

void DrawCylinder(const float, const int, const float, const float);
void DrawGyroscope(const float, const int, const float, const float);
void DrawDistortedCylinder(const float, const int, const float, const float);
void DrawSandClock(const float, const int, const float, const float, const float);

int main(void)
{
    const int VIEWPORT_X_OFFSET = 0;
    const int VIEWPORT_Y_OFFSET = 0;
    const double VIEWPORT_SCALER = 15.0;
    const int VIEWPORT_INITIAL_WIDTH = 1920;
    const int VIEWPORT_INITIAL_HEIGHT = 1080;

    const double CAMERA_FOV = 90.0;
    const double CAMERA_OFFSET_Z = 10.0;
    const double CAMERA_NEAR_CLIPPING_PLANE = 0.01;
    const double CAMERA_FAR_CLIPPING_PLANE = 100.0;

    const double MIN_DELTA_TIME = 0.05;

    const int CYLINDER_SIDES_COUNT = 20;
    const float CYLINDER_HEIGHT = 10.0f;
    const float CYLINDER_RADIUS_CIRCUMCIRCLE_BASE = 3.0f;

    const int GYROSCOPE_SIDES_COUNT = 15;
    const float GYROSCOPE_HEIGHT = 5.0f;
    const float GYROSCOPE_RADIUS_CIRCUMCIRCLE_BASE = 5.0f;

    const int SAND_CLOCK_SIDES_COUNT = 90;
    const float SAND_CLOCK_HEIGHT = 5.0f;
    const float SAND_RADIUS_CONE = 4.0f;
    const float SAND_RADIUS_MIDDLE = 0.05f;

    const int DISTORTED_CYLINDER_SIDES_COUNT = 15;
    const float DISTORTED_CYLINDER_HEIGHT = 5.0f;
    const float DISTORTED_CYLINDER_RADIUS = 5.0f;

    const float ROTATION_SPEED = 30.0f;
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

    GLFWwindow* const window = glfwCreateWindow(VIEWPORT_INITIAL_WIDTH, VIEWPORT_INITIAL_HEIGHT, "Labwork #3 (3.5). IP-14 Babich Denys", NULL, NULL);

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

        glClearColor(0.969f, 0.663f, 0.847f, 1.0f);

        rotationAngle = fmod(rotationAngle + (ROTATION_SPEED * deltaTime), COMPLETE_CIRCLE);

        #pragma region Cylinder

        glPushMatrix();

        glTranslatef(-18.5f, 0.0f, 0.0f);
        glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);

        DrawCylinder(rotationAngle, CYLINDER_SIDES_COUNT, CYLINDER_HEIGHT, CYLINDER_RADIUS_CIRCUMCIRCLE_BASE);

        glPopMatrix();

        #pragma endregion

        #pragma region Gyroscope

        glPushMatrix();

        glTranslatef(-5.5f, 0.0f, 0.0f);
        glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);

        DrawGyroscope(rotationAngle, GYROSCOPE_SIDES_COUNT, GYROSCOPE_HEIGHT, GYROSCOPE_RADIUS_CIRCUMCIRCLE_BASE);

        glPopMatrix();

        #pragma endregion

        #pragma region SandClock

        glPushMatrix();

        glTranslatef(7.5f, 0.0f, 0.0f);
        glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);

        DrawSandClock(rotationAngle, SAND_CLOCK_SIDES_COUNT, SAND_CLOCK_HEIGHT, SAND_RADIUS_CONE, SAND_RADIUS_MIDDLE);

        glPopMatrix();

        #pragma endregion

        #pragma region DistortedCylinder

        glPushMatrix();

        glTranslatef(20.0f, 0.0f, 0.0f);
        glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);

        DrawDistortedCylinder(rotationAngle, DISTORTED_CYLINDER_SIDES_COUNT, DISTORTED_CYLINDER_HEIGHT, DISTORTED_CYLINDER_RADIUS);

        glPopMatrix();

        #pragma endregion

        deltaTime = glfwGetTime() - startTime;
        deltaTime = deltaTime < MIN_DELTA_TIME ? MIN_DELTA_TIME : deltaTime;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}

void DrawDistortedCylinder(const float angle, const int sidesCount, const float height, const float radius)
{
    const float DELTA_FI = 2.0f * M_PI / sidesCount;

    float fi = 0.0f;

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= sidesCount; ++i)
    {
        float red = std::abs(std::sin(2 * angle * M_PI / 180 - fi));
        float blue = std::abs(std::sin(3 * angle * M_PI / 180 - fi));

        glColor3f(red, 0.0f, blue);
        glVertex3f(radius * cos(fi) * sin(angle * M_PI / 180), radius * sin(fi) * cos(angle * M_PI / 180), -height / 2);

        red = std::abs(std::sin(5 * angle * M_PI / 180 + fi));
        blue = std::abs(std::sin(7 * angle * M_PI / 180 + fi));

        glColor3f(red, 1.0f, blue);
        glVertex3f(radius * cos(fi) * cos(angle * M_PI / 180), radius * sin(fi) * sin(angle * M_PI / 180), height / 2);

        fi += DELTA_FI;
    }

    glEnd();
}

void DrawCylinder(const float angle, const int sidesCount, const float height, const float radiusCircumcircleBase)
{
    const float DELTA_FI = 2.0f * M_PI / sidesCount;

    float fi = 0.0f;

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= sidesCount; ++i)
    {
        float red = std::abs(std::sin(2 * angle * M_PI / 180));
        float blue = std::abs(std::sin(3 * angle * M_PI / 180));

        glColor3f(red, 0.5f, blue);
        glVertex3f(radiusCircumcircleBase * cos(fi), radiusCircumcircleBase * sin(fi), -height / 2.0f);

        red = std::abs(std::sin(5 * angle * M_PI / 180));
        blue = std::abs(std::sin(7 * angle * M_PI / 180));

        glColor3f(red, 1.0f, blue);
        glVertex3f(radiusCircumcircleBase * cos(fi), radiusCircumcircleBase * sin(fi), height / 2.0f);

        fi += DELTA_FI;
    }

    glEnd();
}

void DrawGyroscope(const float angle, const int sidesCount, const float height, const float radiusCircumcircleBase)
{
    const float DELTA_FI = 2.0f * M_PI / sidesCount;

    float fi = 0.0f;

    for (int k = 0; k <= 1; ++k)
    {
        fi = 0.0f;

        glBegin(GL_TRIANGLE_FAN);

        glColor3f(1.0f - std::abs(std::sin(5 * angle * M_PI / 180 - fi)), 0.0f, 1.0f - std::abs(std::sin(3 * angle * M_PI / 180 - fi)));
        glVertex3f(0, 0, height - k * 2 * height);

        for (int i = 0; i <= sidesCount; ++i)
        {
            float red = std::abs(std::sin(5 * angle * M_PI / 180 - fi));
            float blue = std::abs(std::sin(3 * angle * M_PI / 180 - fi));

            glColor3f(red, 1.0f - red, blue);
            glVertex3f(radiusCircumcircleBase * cos(fi), radiusCircumcircleBase * sin(fi), 0);

            fi += DELTA_FI;
        }

        glEnd();
    }
}

void DrawSandClock(const float angle, const int sidesCount, const float height, const float radiusTop, const float radiusBottom)
{
    const float DELTA_FI = 2.0f * M_PI / sidesCount;

    float fi = 0.0f;

    for (int k = 0; k <= 1; ++k)
    {
        fi = 0.0f;
        glBegin(GL_QUAD_STRIP);

        for (int i = 0; i <= sidesCount; ++i)
        {
            float red = std::abs(std::sin(2 * angle * M_PI / 180 - fi));
            float blue = std::abs(std::sin(3 * angle * M_PI / 180 - fi));
            float green = std::abs(std::sin(angle * M_PI / 180 + fi));

            glColor3f(red, green, blue);
            glVertex3f(radiusTop * cos(fi), radiusTop * sin(fi), -height + 2 * height * k);

            red = std::abs(std::sin(5 * angle * M_PI / 180 + fi));
            blue = std::abs(std::sin(7 * angle * M_PI / 180 + fi));
            green = std::abs(std::sin(3 * angle * M_PI / 180 + fi));

            glColor3f(red, green, blue);
            glVertex3f(radiusBottom * cos(fi), radiusBottom * sin(fi), 0);

            fi += DELTA_FI;
        }

        glEnd();
    }
}