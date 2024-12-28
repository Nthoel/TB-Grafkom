#include <GL/glut.h>
#include <math.h>

float tx = 0.0f, ty = 0.0f, tz = 0.0f;    // Translasi
float rx = 0.0f, ry = 0.0f, rz = 0.0f;    // Rotasi
float sx = 1.0f, sy = 1.0f, sz = 1.0f;    // Skala
bool showAxis = true;                      // Toggle sumbu

void init() {
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

void display() {
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

void reshape(int w, int h) {
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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("SolidTorus dengan Transformasi");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
