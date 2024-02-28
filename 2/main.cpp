#include <cstdlib>

#include <glut/src/glut.h>
#include <GLFW/src/glfw3.h>

void DrawCube(void);

int main(void)
{
    const int VIEWPORT_WIDTH = 1920;
    const int VIEWPORT_HEIGHT = 1080;

    if (!glfwInit())
    {
        return EXIT_FAILURE;
    }

    GLFWwindow* const window = glfwCreateWindow(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, "Labwork #2. IP-14 Babich Denys", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

    glEnable(GL_DOUBLEBUFFER);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glPushMatrix();

        //glClearColor(1.0, 1.0, 1.0, 0.0);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        //glTranslatef(0.0, 0.0, -5.0);

        DrawCube();

        //glu

        //gluPerspective

        //    gluLookAt(0.0, 0.0, 8.0, // позиція камери
        // ////////
        //        0.0, 0.0, 0.0, // напрям на центр сцени
        //        0.0, 1.0, 0.0);// напрям вертикалі

        //    glRotatef(Angle, 1.0, 1.0, 1.0);

        //    // batch call

        //    glPopMatrix();

        //Angle: = Angle + 1.0; // зміна кута для обертання сцени
        //    if Angle >= 360.0 then Angle : = 0.0 end;

        //    glViewport(0, 0, ClientWidth, ClientHeight);

        //    glMatrixMode(GL_PROJECTION);
        //    glLoadIdentity; // завантажумо одиничну матрицю

        //    glOrtho( // xmin, xmax, ymin, ymax, znear, zfar
        //        -w * ClientWidth / ClientHeight,
        //        w * ClientWidth / ClientHeight, -w, w, 1, 10);
        //    // встановлюємо модельну матрицю
        //    glMatrixMode(GL_MODELVIEW);
        //    glLoadIdentity; // завантажуємо одиничну матрицю



        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void DrawCube(void)
{
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.0f);  // Bottom-left vertex
    glVertex3f(0.5f, -0.5f, 0.0f);   // Bottom-right vertex
    glVertex3f(0.5f, 0.5f, 0.0f);    // Top-right vertex
    glVertex3f(-0.5f, 0.5f, 0.0f);   // Top-left vertex
    glEnd();

    //const float h = 1.0;

    //glBegin(GL_QUADS);

    //glNormal3f(0.0, 0.0, 1.0);

    //glColor3f(1.0, 0.0, 0.0);

    //glVertex3f(h, h, h); // A
    //glVertex3f(-h, h, h); // B
    //glVertex3f(-h, -h, h); // C
    //glVertex3f(h, -h, h); // D


    //glColor3f(0.0, 0.0, 1.0); 
    //glNormal3f(1.0, 0.0, 0.0);

    //glVertex3f(h, h, -h); // A1 права грань куба
    //glVertex3f(h, h, h); // A (синій колір)
    //glVertex3f(h, -h, h); // D
    //glVertex3f(h, -h, -h); // D1

    //glColor3f(0.0, 1.0, 0.0); 
    //glNormal3f(0.0, 0.0, -1.0);

    //glVertex3f(-h, h, -h); // B1 задня грань куба
    //glVertex3f(h, h, -h); // A1 (зелений колір)
    //glVertex3f(h, -h, -h); // D1
    //glVertex3f(-h, -h, -h); // C1

    //glColor3f(1.0, 1.0, 0.0); 
    //glNormal3f(-1.0, 0.0, 0.0);

    //glVertex3f(-h, h, h); // B
    //glVertex3f(-h, h, -h); // B1
    //glVertex3f(-h, -h, -h); // B1
    //glVertex3f(-h, -h, h); // C
}

//TODO: DO