#include <GL/glut.h>
#include <math.h>

float progress = 0.0;
void initSecondsScene();
void initFirstScene();
int window_id = -1;
void changeScene(const char *title, void (*displayCallback)(void), void (*initCallback)(void));
void mainScene();

void loadingScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3ub(255,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(-80,-5);
    glVertex2d(-80,5);
    glVertex2d(80,5);
    glVertex2d(80,-5);
    glEnd();

    float bar =- 80+ (80* (progress*2));
    glBegin(GL_QUADS);
    glVertex2d(-80,-5);
    glVertex2d(-80,5);
    glVertex2d(bar, 5);
    glVertex2d(bar, -5);
    glEnd();
    glFlush();
    glutPostRedisplay();

    if (progress < 1.0)
    {
        progress +=0.0001;
    }
    else
    {
        changeScene("Polyhedra 3D", mainScene, initSecondsScene);
    }
}

void drawCartecius()
{
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    glVertex3f(-50.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);

    glVertex3f(0.0, -50.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);

    glVertex3f(0.0, 0.0, -50.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();
}
float tick = 0.0;

void mainScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawCartecius();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(5.0);
    glBegin(GL_LINE_STRIP);
    for (float x = -6.28f; x <= 6.28f; x += 0.1f)
    {
        float y = (5.0f* sin(x+tick));
        float z=((0.1f+x)*cos(x+tick));
        glVertex3f(x, y, z);
    }
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (float x = -6.28f; x <= 6.28f; x += 0.1f)
    {
        float y = (5.0f * sin(x+ tick * 2.0f));
        float z=((0.1f+x)*cos(x+tick*2.0f));
        glVertex3f(z, y, x); 
    }
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (float x = -6.28f * 1.5f; x <= 6.28f *1.5f; x +=0.1f)
    {
        float y = (5.0f* sin(x+tick*2.0f));
        float z= ((0.1f +x)* cos(x+tick*2.0f));
        glVertex3f(z, x, y);
    }
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
    tick += 0.001;
}

void initFirstScene()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void initSecondsScene()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1.0, 100.0);
    gluLookAt(10.0, 10.0, 17.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void changeScene(const char *title, void (*displayCallback)(void), void (*initCallback)(void))
{
    if (window_id != -1)
    glutDestroyWindow(window_id);
    window_id = glutCreateWindow(title);
    glutDisplayFunc(displayCallback);
    initCallback();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 0);
    changeScene("loading ... ", loadingScreen, initFirstScene);
    glutMainLoop();
    return 0;
}