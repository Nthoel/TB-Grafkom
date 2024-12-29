#include <GL/glew.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <stdio.h>
#include <math.h>

// Variables for the first window (hehe.cpp)
float tx = 0.0f, ty = 0.0f, tz = 0.0f;    // Translasi
float rx = 0.0f, ry = 0.0f, rz = 0.0f;    // Rotasi
float sx = 1.0f, sy = 1.0f, sz = 1.0f;    // Skala
bool showAxis = true;                      // Toggle sumbu

// Variables for the second window (bambu.cpp)
float angle = 0.0f;
float speed = 3.0f;

GLuint texture_Earth_ID;

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

    glPushMatrix();
    // X-axis (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    // Y-axis (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    // Z-axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glPopMatrix();

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

void createObject() {
    GLUquadric* object = gluNewQuadric();
    gluQuadricTexture(object, GL_TRUE);
    gluQuadricNormals(object, GLU_SMOOTH);
    
    float panjang = 3.0f;  // Sesuaikan dengan ukuran yang diinginkan
    float lebar = 2.0f;    // Sesuaikan dengan ukuran yang diinginkan
    float tinggi = 0.5f;   // Sesuaikan dengan ukuran yang diinginkan


    glBegin(GL_QUADS);
    // Sisi depan
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-panjang, -tinggi, lebar);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(panjang, -tinggi, lebar);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(panjang, tinggi, lebar);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-panjang, tinggi, lebar);
    
    // Sisi belakang
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-panjang, -tinggi, -lebar);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-panjang, tinggi, -lebar);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(panjang, tinggi, -lebar);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(panjang, -tinggi, -lebar);
    
    // Sisi atas
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-panjang, tinggi, -lebar);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-panjang, tinggi, lebar);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(panjang, tinggi, lebar);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(panjang, tinggi, -lebar);
    
    // Sisi bawah
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-panjang, -tinggi, -lebar);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(panjang, -tinggi, -lebar);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(panjang, -tinggi, lebar);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-panjang, -tinggi, lebar);
    
    // Sisi kanan
    glTexCoord2f(1.0f, 0.0f); glVertex3f(panjang, -tinggi, -lebar);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(panjang, tinggi, -lebar);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(panjang, tinggi, lebar);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(panjang, -tinggi, lebar);
    
    // Sisi kiri
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-panjang, -tinggi, -lebar);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-panjang, -tinggi, lebar);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-panjang, tinggi, lebar);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-panjang, tinggi, -lebar);
    glEnd();
}

void displayintro(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(0,0,0,0);
    
 
    //BIND TExture ke Object di bawahnya, dengan ID yang sudah di simpan 
    //tadi
    glBindTexture( GL_TEXTURE_2D, texture_Earth_ID);
    createObject();
 
 
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}

    GLuint textureID = 0;

int loadTexture(const char* path) {
    //untuk menyimpan Data Texture di ID spesifik!
    glGenTextures(1, &textureID);
    //kode di bawah untuk Memproses Pembacaan/Penyimpanan Buffer dari 
    //Gambar
    void* imgData;
    int imgWidth;
    int imgHeight;
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(path);
    if (format == FIF_UNKNOWN) {
    printf("Unknown file type for texture image file %s\n", path);
    return -1;
 }
    FIBITMAP* bitmap = FreeImage_Load(format, path, 0);
    if (!bitmap) {
    printf("Failed to load image %s\n", path);
    return -1;
 }
    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);
    FreeImage_Unload(bitmap);
    imgData = FreeImage_GetBits(bitmap2);
    imgWidth = FreeImage_GetWidth(bitmap2);
    imgHeight = FreeImage_GetHeight(bitmap2);
    if (imgData) {
    printf("Texture image loaded from file %s, size %dx%d\n", path,
    imgWidth, imgHeight);
    int format;
    if ( FI_RGBA_RED == 0 )
    format = GL_RGB;
    else
    format = GL_BGR;
    glBindTexture( GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0,
    format,GL_UNSIGNED_BYTE, imgData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    textureID++;
    return textureID-1;
 }
    else {
        printf("Failed to get texture data from %s\n", path);
 }
 return -1;
}

void initProjection(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_SMOOTH);
    glShadeModel(GL_SMOOTH);
    //untuk meaktifkan texture di Polygon
    glEnable(GL_TEXTURE_2D);
    //untuk Mengubah matrik menjadi texture Rendering di OpenGL
    glMatrixMode(GL_TEXTURE);
    //END
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,1800/900,1.0,100.0);
    gluLookAt(10.0, 10.0, 10.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    texture_Earth_ID = loadTexture("textures/konnyaku2.png");
    //texture_bulan_ID = loadTexture("textures/bulan.png");
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glewInit();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create the second window (hehe.cpp)
    glutInitWindowSize(800, 600);
    int window1 = glutCreateWindow("Lingkaran Penembus Dinding");
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

    // Create the second window (hehe.cpp)
    glutInitWindowSize(800, 600);
    int window3 = glutCreateWindow("Konnyaku");
    initProjection();
    glutDisplayFunc(displayintro);

    glutMainLoop();
    return 0;
}