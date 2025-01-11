#include <GL/glew.h> // Menggunakan GLEW untuk mengakses semua fungsi OpenGL di Windows 
#include <GL/glut.h> // Menggunakan GLUT untuk membuat jendela dan menangani input
#include <FreeImage.h> // Menggunakan FreeImage untuk memuat gambar
#include <stdio.h> // Menggunakan stdio untuk fungsi printf
#include <math.h> // Menggunakan math untuk fungsi matematika

//---------------------------------------------------------Fathul---------------------------------------------------------//
float tx = 0.0f, ty = 0.0f, tz = 0.0f;    // Translasi
float rx = 0.0f, ry = 0.0f, rz = 0.0f;    // Rotasi
float sx = 1.0f, sy = 1.0f, sz = 1.0f;    // Skala
bool showAxis = true;                      // Toggle sumbu
//------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------Sautan---------------------------------------------------------//
float tx2 = 0.0f, ty2 = 0.0f, tz2 = 0.0f;    // Translasi 
float rx2 = 0.0f, ry2 = 0.0f, rz2 = 0.0f;    // Rotasi
float sx2 = 1.0f, sy2 = 1.0f, sz2 = 1.0f;    // Skala
bool showAxis2 = true;                      // Untuk menampilkan sumbu koordinat
GLuint texture_Earth_ID;
//------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------Wilyandi-------------------------------------------------------//
bool showAxis3 = true;     // Untuk menampilkan sumbu koordinat
bool isRotate = false;     // rotasi baling-baling
bool is2DMode = false;     // 2D
float angle = 0.0f;        // Sudut rotasi baling-baling
float speed = 3.0f;        // Kecepatan rotasi
//------------------------------------------------------------------------------------------------------------------------//


//---------------------------------------------------------Fathul---------------------------------------------------------//
void initHehe() { // Fungsi inisialisasi 
    glClearColor(0.0, 0.0, 0.0, 1.0); // Mengatur warna background menjadi hitam
    glEnable(GL_DEPTH_TEST); // Mengaktifkan depth testing
    
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
    if (!showAxis) return; // Jika showAxis bernilai false, maka keluar dari fungsi
    
    glDisable(GL_LIGHTING); // Menonaktifkan pencahayaan
    glBegin(GL_LINES); // Menggambar sumbu koordinat
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
    glEnable(GL_LIGHTING); // Mengaktifkan pencahayaan kembali
}

void displayHehe() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Membersihkan buffer warna dan kedalaman 
    
    glLoadIdentity(); // Memuat matriks identitas ke matriks modelview
    gluLookAt(5.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Menempatkan kamera pada posisi (5, 5, 15) dan mengarahkan ke titik (0, 0, 0)
    
    drawAxes(); // Memanggil fungsi untuk menggambar sumbu koordinat
    
    glPushMatrix(); // Menyimpan matriks model saat ini ke dalam tumpukan
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
    
    glPopMatrix(); // Mengembalikan matriks model ke kondisi sebelumnya
    glutSwapBuffers(); // Menukar buffer untuk menggambar (double buffering)
}

void reshapeHehe(int w, int h) { // Fungsi untuk menangani event reshape 
    glViewport(0, 0, w, h); // Mengatur viewport sesuai ukuran jendela
    glMatrixMode(GL_PROJECTION); // Beralih ke matriks proyeksi 
    glLoadIdentity(); // Memuat matriks identitas ke matriks proyeksi
    gluPerspective(45.0, (float)w/(float)h, 1.0, 100.0); // Mengatur proyeksi perspektif 
    glMatrixMode(GL_MODELVIEW); // Beralih ke matriks modelview
}

void keyboard(unsigned char key, int x, int y) { // Fungsi untuk menangani event keyboard
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
    glutPostRedisplay(); // Meminta OpenGL untuk merender ulang tampilan
}
//------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------Sautan---------------------------------------------------------//
void keyboard2(unsigned char key, int x, int y) {
    switch(key) {
        // Translasi
       case 'w': ty2 += 0.1f; break; // Menambah posisi objek pada sumbu Y (ke atas)
       case 's': ty2 -= 0.1f; break; // Mengurangi posisi objek pada sumbu Y (ke bawah)
       case 'a': tx2 -= 0.1f; break; // Mengurangi posisi objek pada sumbu X (ke kiri)
       case 'd': tx2 += 0.1f; break; // Menambah posisi objek pada sumbu X (ke kanan)
       case 'q': tz2 -= 0.1f; break; // Mengurangi posisi objek pada sumbu Z (menjauh)
       case 'e': tz2 += 0.1f; break; // Menambah posisi objek pada sumbu Z (mendekat)

        
        // Rotasi
        case 'i': rx2 += 5.0f; break; // Menambah rotasi pada sumbu X (memutar ke depan)
        case 'k': rx2 -= 5.0f; break; // Mengurangi rotasi pada sumbu X (memutar ke belakang)
        case 'j': ry2 -= 5.0f; break; // Mengurangi rotasi pada sumbu Y (memutar ke kiri)
        case 'l': ry2 += 5.0f; break; // Menambah rotasi pada sumbu Y (memutar ke kanan)
        case 'u': rz2 -= 5.0f; break; // Mengurangi rotasi pada sumbu Z (memutar ke arah negatif Z)
        case 'o': rz2 += 5.0f; break; // Menambah rotasi pada sumbu Z (memutar ke arah positif Z)

        
        // Skala
        case '+': sx2 += 0.1f; sy2 += 0.1f; sz2 += 0.1f; break; // Menambah skala objek pada semua sumbu (memperbesar)
        case '-': sx2 -= 0.1f; sy2 -= 0.1f; sz2 -= 0.1f; break; // Mengurangi skala objek pada semua sumbu (memperkecil)

        
        // Toggle sumbu
        case 'h': showAxis2 = !showAxis2; break; // Mengaktifkan/mematikan visualisasi sumbu koordinat

        
        case 27: exit(0); break; // Menutup program saat tombol ESC (kode ASCII 27) ditekan

    }
    glutPostRedisplay(); // Meminta OpenGL untuk merender ulang tampilan

}
//------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------Wilyandi-------------------------------------------------------//
void keyboard3(unsigned char key, int x, int y) {
    switch(key) {
        // Toggle sumbu
        case 'h': showAxis3 = !showAxis3; break; // Mengaktifkan/mematikan visualisasi sumbu koordinat
        
        case 27: exit(0); break; // Menutup program saat tombol ESC (kode ASCII 27) ditekan
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
    if (!showAxis3) return;
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
    if (isRotate) {
        angle += speed;
        if (angle > 360.0f) angle -= 360.0f;
    }
    glutPostRedisplay();
}
//------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------Sautan---------------------------------------------------------//
void createObject() {
    GLUquadric* object = gluNewQuadric(); // Membuat objek kuadrik OpenGL untuk tekstur
    gluQuadricTexture(object, GL_TRUE); // Mengaktifkan tekstur pada objek kuadrik
    gluQuadricNormals(object, GLU_SMOOTH); // Menambahkan normal yang mulus untuk pencahayaan

    
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

void displayKonnyaku(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Membersihkan buffer warna dan kedalaman
    glPushMatrix(); // Menyimpan matriks model saat ini ke dalam tumpukan
    glTranslatef(tx2, ty2, tz2); // Melakukan translasi objek berdasarkan nilai variabel
    glRotatef(rx2, 1.0, 0.0, 0.0); // Rotasi pada sumbu X
    glRotatef(ry2, 0.0, 1.0, 0.0); // Rotasi pada sumbu Y
    glRotatef(rz2, 0.0, 0.0, 1.0); // Rotasi pada sumbu Z
    glScalef(sx2, sy2, sz2); // Skala objek sesuai nilai variabel

 
    //BIND TExture ke Object di bawahnya, dengan ID yang sudah di simpan 
    //tadi
    glBindTexture(GL_TEXTURE_2D, texture_Earth_ID); // Mengaktifkan tekstur pada objek
    createObject(); // Memanggil fungsi untuk menggambar objek
 
 
    glPopMatrix(); // Mengembalikan matriks model ke kondisi sebelumnya
    glutSwapBuffers(); // Menukar buffer untuk menggambar (double buffering)
    glutPostRedisplay(); // Meminta OpenGL untuk merender ulang
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
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(path); // Mendapatkan format file gambar
    if (format == FIF_UNKNOWN) {
    printf("Unknown file type for texture image file %s\n", path);
    return -1;
 }
    FIBITMAP* bitmap = FreeImage_Load(format, path, 0); // Memuat gambar
    if (!bitmap) {
    printf("Failed to load image %s\n", path);
    return -1;
 }
    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap); // Mengonversi gambar ke 24-bit RGB
    FreeImage_Unload(bitmap);
    imgData = FreeImage_GetBits(bitmap2); // Mendapatkan data piksel gambar
    imgWidth = FreeImage_GetWidth(bitmap2); // Mendapatkan lebar gambar
    imgHeight = FreeImage_GetHeight(bitmap2); // Mendapatkan tinggi gamba
    if (imgData) {
    printf("Texture image loaded from file %s, size %dx%d\n", path,
    imgWidth, imgHeight);
    int format;
    if ( FI_RGBA_RED == 0 )
    format = GL_RGB;
    else
    format = GL_BGR;
    glBindTexture(GL_TEXTURE_2D, textureID); // Mengikat tekstur dengan ID tertentu
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0,
    format, GL_UNSIGNED_BYTE, imgData); // Mengisi data tekstur
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Mengatur filter tekstur
    textureID++;
    return textureID-1;
 }
    else {
        printf("Failed to get texture data from %s\n", path);
 }
 return -1;
}

void initProjection(){
    glEnable(GL_DEPTH_TEST); // Mengaktifkan pengujian kedalaman untuk 3D
    glEnable(GL_POLYGON_SMOOTH); // Menghaluskan tepi poligon
    glShadeModel(GL_SMOOTH);
    //untuk meaktifkan texture di Polygon
    glEnable(GL_TEXTURE_2D);
    //untuk Mengubah matrik menjadi texture Rendering di OpenGL
    glMatrixMode(GL_TEXTURE);
    //END
    glMatrixMode(GL_PROJECTION); // Beralih ke matriks proyeksi
    glLoadIdentity(); // Memuat identitas awal
    gluPerspective(45.0, 1800/900, 1.0, 100.0); // Mengatur proyeksi perspektif
    gluLookAt(10.0, 10.0, 10.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW); // Beralih ke mode matriks model/view
    texture_Earth_ID = loadTexture("textures/konnyaku2.png"); // Memuat tekstur dari file
    //texture_bulan_ID = loadTexture("textures/bulan.png");
}
//------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------Wilyandi-------------------------------------------------------//
//fungsi untuk proses menu GUI
void processMenu(int option) {
    switch (option) {
        case 1:
            isRotate = true;	//Memutar baling baling
            break;
        case 2:
            isRotate = false;	//stop putar
            break;
        case 3:
            exit(0);	//keluar dri program
            break;
    }
    glutPostRedisplay();
}
//Buat menu klik kanan
void createMenu() {
    glutCreateMenu(processMenu);	//Hubungkan menu dengan fungsi processMenu
    glutAddMenuEntry("Putar", 1);	//Tambah opsi "Putar"
    glutAddMenuEntry("Berhenti", 2);	//Tambah opsi "Berhenti"
    glutAddMenuEntry("Keluar", 3);	//Tambah opsi "Keluar"
    glutAttachMenu(GLUT_RIGHT_BUTTON); //Tampilkan menu saat klik kanan
}
//------------------------------------------------------------------------------------------------------------------------//



int main(int argc, char** argv) { // Fungsi utama
    glutInit(&argc, argv); // Menginisialisasi GLUT
    glewInit(); // Menginisialisasi GLEW
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Mengatur mode tampilan GLUT 

//---------------------------------------------------------Fathul---------------------------------------------------------//
    glutInitWindowSize(400, 400); // Mengatur ukuran jendela
    glutInitWindowPosition(1000, 200); // Mengatur posisi jendela  
    int window1 = glutCreateWindow("Lingkaran Penembus Dinding"); // Membuat jendela dengan judul tertentu
    initHehe(); // Memanggil fungsi inisialisasi
    glutDisplayFunc(displayHehe); // Memanggil fungsi display
    glutReshapeFunc(reshapeHehe); // Memanggil fungsi reshape
    glutKeyboardFunc(keyboard); // Memanggil fungsi keyboard
//------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------Wilyandi-------------------------------------------------------//
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(150, 200);
    int window2 = glutCreateWindow("Baling baling bambu");
    initBambu();
    glutDisplayFunc(displayBambu);
    glutReshapeFunc(reshapeBambu);
    glutKeyboardFunc(keyboard3);
    glutIdleFunc(idleBambu);
    createMenu();
//------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------Sautan---------------------------------------------------------//
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(575, 200);
    int window3 = glutCreateWindow("Konnyaku");
    initProjection();
    glutDisplayFunc(displayKonnyaku);
    glutKeyboardFunc(keyboard2);
//------------------------------------------------------------------------------------------------------------------------//

    glutMainLoop();
    return 0;
}