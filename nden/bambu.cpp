#include <GL/glut.h>

float angle = 0.0f;
float speed = 3.0f;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to white
    glEnable(GL_DEPTH_TEST); // Enable depth testing
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void drawAxes() {
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // X-axis (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);

    // Y-axis (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);

    // Z-axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);

    glEnd();
}

void drawPropeller() {
    // Draw the rotating propeller
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis

    // Draw the blade
    glPushMatrix();
    glScalef(7.0f, 0.2f, 0.5f);
    glColor3f(1.0f, 0.8f, 0.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();

    // Draw the central hub
    glColor3f(1.0f, 0.7f, 0.0f);
    glutSolidSphere(0.5f, 20, 20);
}

void drawStand() {
    // Draw the vertical pole
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.0f);
    glScalef(0.2f, 5.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw the base
    glPushMatrix();
    glColor3f(1.0f, 0.7f, 0.0f);
    glTranslatef(0.0f, -2.5f, 0.0f);
    glutSolidSphere(0.8f, 20, 20);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(10.0, 10.0, 17.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Draw the coordinate axes
    drawAxes();

    // Draw the stand
    drawStand();

    // Move the propeller to the top of the stand
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    drawPropeller();
    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
    angle += speed;
    if (angle > 360.0f) angle -= 360.0f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Baling baling bambu");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}