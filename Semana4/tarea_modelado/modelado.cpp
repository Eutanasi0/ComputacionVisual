#include <GL/glut.h>
#include <math.h>

void anillo(float R, float y, int N);
float dameX(float R, int N, int n);
float dameZ(float R, int N, int n);
void formaAlambre(float H, int N);

void anillo(float R, float y, int N) {
	int i;
	float x, z;
	
	glBegin(GL_LINE_LOOP);
	for(i = 0; i < N; i++) {
		x = dameX(R, N, i);
		z = dameZ(R, N, i);
		glVertex3f(x, y, z);
	}
	glEnd();
}

float dameX(float R, int N, int n) {
	return (float) R * cos(n * (2 * M_PI) / N);
}

float dameZ(float R, int N, int n) {
	return (float) R * sin(n * (2 * M_PI) / N);
}

void formaAlambre(float H, int N) {
	int i;
	float y, r_cono;
	
	for(i = 0; i < N; i++) { 
		y = i * H / N; // Para cada nivel de altura
		r_cono = (H - y) / H * 50.0; // Radio del cono en funci?n de la altura
		anillo(r_cono, y - (H / 2), N); // dibujamos un anillo para el cono
	}
}

void display(void) {
	glClearColor (1.0,1.0,1.0, 1.0);
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glLoadIdentity ();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -4.0f);
	glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
	formaAlambre(100.0f, 20); // Solo para mantener la llamada a formaAlambre
	glPopMatrix();
	glFlush ();
}

void inicializaVista(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int width, int height) {
	glViewport (0, 0, width, height);
	inicializaVista ();
}

void inicializaVentana(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (700, 700);
	glutInitWindowPosition (200, 30);
	glutCreateWindow (argv[0]);
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
}

void iniciaOpenGL(int argc, char **argv) {
	inicializaVentana (argc, argv);
	inicializaVista ();
	glutMainLoop();
}

int main (int argc, char** argv) {
	iniciaOpenGL(argc, argv);
	return (1);
}
