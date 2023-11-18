#include <iostream>
#include <stdlib.h>
#include <glut.h>
using namespace std;

float rotateX = 0.0f;
float rotateY = 0.0f;
int selectedObject = 0;
float w = 480, h = 480;
float sudut = 0, sx = 0, sy = 0, sz = 0;
float z_pos = -10.0f;
float rot = 0.0f;

void cube() {
	glColor3d(0, 0, 0);
	glutWireCube(10);
}

void sphere() {
	glColor3d(0, 0, 0);
	glutWireSphere(10, 5, 3);
}

void cone() {
	glColor3d(0, 0, 0);
	glutWireCone(5, 10, 20, 20);
}

void torus() {
	glColor3d(0, 0, 0);
	glutWireTorus(1, 10, 50, 20);
}

void Dodecahedron() {
	glColor3d(0, 0, 0);
	glutWireDodecahedron();
}

void Teapot() {
	glColor3d(0, 0, 0);
	glutWireTeapot(10);
}

void combinedObjects() {
	glColor3d(0, 0, 0);
	glutWireCube(15);
	glColor3d(0, 0, 1);
	glutWireTeapot(5);
	glColor3d(0, 1, 0);
	glutWireTorus(1, 10, 50, 20);
	glColor3d(1, 0, 0);
	glutWireDodecahedron();
}

void initGL() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45., (GLdouble)w / (GLdouble)h, 1., 1000.);  
	glMatrixMode(GL_MODELVIEW);
}

void drawSelectedObject() {
	switch (selectedObject) {
	case 1:
		cube();
		break;
	case 2:
		sphere();
		break;
	case 3:
		cone();
		break;
	case 4:
		torus();
		break;
	case 5:
		Dodecahedron();
		break;
	case 6:
		Teapot();
		break;
	case 7:
		combinedObjects();
		break;
	default:
		cout << "Invalid Choice";
		break;
	}
}

void resize(int w1, int h1) {
	glViewport(0, 0, w1, h1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w1 / (float)h1, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

float initialRot = 0.0f; // untuk menyimpan nilai rotasi awal
bool clockwiseRotation = true; // untuk menyimpan arah rotasi
bool autoRotate = false; // simpan status rotasi otomatis
void toggleAutoRotate(char direction) {
	if (direction == 'q' || direction == 'Q') {
		autoRotate = !autoRotate;
		if (!autoRotate) {
			// Jika rotasi otomatis dimatikan, simpan nilai rotasi saat ini
			// supaya tidak mereset posisi objek
			initialRot = rot;
		}
		clockwiseRotation = false;  // atur arah rotasi objek ke kiri
	}
	else if (direction == 'r' || direction == 'R') {
		autoRotate = !autoRotate;
		if (!autoRotate) {
			// Jika rotasi otomatis dimatikan, simpan nilai rotasi saat ini
			// supaya tidak mereset posisi objek
			initialRot = rot;
		}
		clockwiseRotation = true;   // atur arah rotasi objek ke ke kanan
	}
	glutPostRedisplay(); // Meminta redisplay saat status rotasi otomatis diubah
}

void myTimeOut(int id) {
	if (autoRotate) {
		if (clockwiseRotation) {
			rot += 1.0f;  // atur kecepatan rotasi keKANAN
		}
		else {
			rot -= 1.0f;  // atur kecepatan rotasi keKIRI
		}
		glutPostRedisplay();
	}
	glutTimerFunc(16, myTimeOut, 0);
}

void myKeyboard(unsigned char key, int x, int y) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (key == 'w') {
		rotateX -= 10.0f;
	}
	if (key == 's') {
		rotateX += 10.0f;
	}
	if (key == 'd') {
		rotateY += 10.0f;
	}
	if (key == 'a') {
		rotateY -= 10.0f;
	}
	if (key == '<' || key == ',') {
		z_pos -= 0.5f;
	}
	if (key == '>' || key == '.') {
		z_pos += 0.5f;
	}
	if (key == 'q' || key == 'Q' || key == 'r' || key == 'R') {
		toggleAutoRotate(key);
	}
	glutPostRedisplay();
}

void update(int value) {
	glutTimerFunc(16, update, 0);  //60 fps
}

void displayObjectMenu() {
	cout << "0. Exit \n";
	cout << "1. Cube \n";
	cout << "2. Sphere \n";
	cout << "3. Cone \n";
	cout << "4. Torus \n";
	cout << "5. Dodecahedron \n";
	cout << "6. Teapot \n";
	cout << "7. combinedObjects \n";
	cout << "Your Choice Brodie ? : ";
	cin >> selectedObject;

	if (selectedObject == 0) {
		exit(0);  //keluar dari program
	}
}

void mydisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0f, z_pos);
	glRotatef(rot, 0, 1, 0);

	glRotatef(rotateX, 1, 0, 0);
	glRotatef(rotateY, 0, 1, 0);

	drawSelectedObject();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	displayObjectMenu();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(w, h);
	glutCreateWindow("OpenGL Objects");
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(resize);
	initGL();
	glutTimerFunc(16, myTimeOut, 0);  // Ganti waktu timeout dengan nilai yang lebih sesuai untuk menghasilkan 60 fps
	glutKeyboardFunc(myKeyboard);
	glutMainLoop();
	return 0;
}
