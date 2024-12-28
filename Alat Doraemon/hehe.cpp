#include <GL/glut.h>
#include <math.h>

// Variables for the first window (hehe.cpp)
float tx = 0.0f, ty = 0.0f, tz = 0.0f;    // Translasi
float rx = 0.0f, ry = 0.0f, rz = 0.0f;    // Rotasi
float sx = 1.0f, sy = 1.0f, sz = 1.0f;    // Skala
bool showAxis = true;                      // Toggle sumbu

// Variables for the second window (bambu.cpp)
float angle = 0.0f;
float speed = 3.0f;

void initHehe() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    
    // Aktifkan pencahayaan
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Konfigurasi cahaya
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void drawAxes() {
    if (!showAxis) return;
    
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    // X-axis (merah)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-10.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    // Y-axis (hijau)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -10.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    // Z-axis (biru)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -10.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
    glEnable(GL_LIGHTING);
}

void displayHehe() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    drawAxes();
    
    glPushMatrix();
    // Transformasi
    glTranslatef(tx, ty, tz);
    glRotatef(rx, 1.0, 0.0, 0.0);
    glRotatef(ry, 0.0, 1.0, 0.0);
    glRotatef(rz, 0.0, 0.0, 1.0);
    glScalef(sx, sy, sz);
    
    // Material untuk torus (kuning)
    GLfloat yellow_material[] = {1.0, 1.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow_material);
    
    // Gambar solid torus
    glutSolidTorus(0.2, 1.5, 50, 50);
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshapeHehe(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/(float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        // Translasi
        case 'w': ty += 0.1f; break;
        case 's': ty -= 0.1f; break;
        case 'a': tx -= 0.1f; break;
        case 'd': tx += 0.1f; break;
        case 'q': tz -= 0.1f; break;
        case 'e': tz += 0.1f; break;
        
        // Rotasi
        case 'i': rx += 5.0f; break;
        case 'k': rx -= 5.0f; break;
        case 'j': ry -= 5.0f; break;
        case 'l': ry += 5.0f; break;
        case 'u': rz -= 5.0f; break;
        case 'o': rz += 5.0f; break;
        
        // Skala
        case '+': sx += 0.1f; sy += 0.1f; sz += 0.1f; break;
        case '-': sx -= 0.1f; sy -= 0.1f; sz -= 0.1f; break;
        
        // Toggle sumbu
        case 'h': showAxis = !showAxis; break;
        
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void initBambu() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to white
    glEnable(GL_DEPTH_TEST); // Enable depth testing
}

void reshapeBambu(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void drawAxesBambu() {
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

void displayBambu() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(10.0, 10.0, 17.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Draw the coordinate axes
    drawAxesBambu();

    // Draw the stand
    drawStand();

    // Move the propeller to the top of the stand
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    drawPropeller();
    glPopMatrix();

    glutSwapBuffers();
}

void idleBambu() {
    angle += speed;
    if (angle > 360.0f) angle -= 360.0f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create the first window (hehe.cpp)
    glutInitWindowSize(800, 600);
    int window1 = glutCreateWindow("SolidTorus dengan Transformasi");
    initHehe();
    glutDisplayFunc(displayHehe);
    glutReshapeFunc(reshapeHehe);
    glutKeyboardFunc(keyboard);

    // Create the second window (bambu.cpp)
    glutInitWindowSize(800, 600);
    int window2 = glutCreateWindow("Baling baling bambu");
    initBambu();
    glutDisplayFunc(displayBambu);
    glutReshapeFunc(reshapeBambu);
    glutIdleFunc(idleBambu);

    glutMainLoop();
    return 0;
}