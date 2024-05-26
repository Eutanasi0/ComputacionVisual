#include <GL/glut.h>

// Variables globales 
// Proyeccion ortogonal
GLfloat leftOrtho = -4.0f, rightOrtho = 4.0f, bottomOrtho = -4.0f, topOrtho = 4.0f, zNearOrtho = 1.0f, zFarOrtho = 8.0f;
// Proyeccion de perspeciva
GLfloat fov = 45.0f, zNearPersp = 1.0f, zFarPersp = 4.8f;

GLfloat anguloCuboX = 0.0f;  
GLfloat anguloCuboY = 0.0f; 
GLfloat anguloEsfera = 0.0f; 
GLint ancho, alto; 
int hazPerspectiva = 1; 

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	
	if (hazPerspectiva) {
		gluPerspective(fov, (GLfloat)width / (GLfloat)height, zNearPersp, zFarPersp);
	} else {
		glOrtho(leftOrtho, rightOrtho, bottomOrtho, topOrtho, zNearOrtho, zFarOrtho);
	}
	
	glMatrixMode(GL_MODELVIEW);
	
	ancho = width; 
	alto = height; 
}

void drawCube(void) {
	glColor3f(1.0f, 0.0f, 0.0f); 
	glBegin(GL_QUADS);  //cara frontal 
	glVertex3f(-1.0f, -1.0f,  1.0f); 
	glVertex3f( 1.0f, -1.0f,  1.0f); 
	glVertex3f( 1.0f,  1.0f,  1.0f); 
	glVertex3f(-1.0f,  1.0f,  1.0f); 
	glEnd(); 
	
	glColor3f(0.0f, 1.0f, 0.0f); 
	glBegin(GL_QUADS);  //cara trasera 
	glVertex3f( 1.0f, -1.0f, -1.0f); 
	glVertex3f(-1.0f, -1.0f, -1.0f); 
	glVertex3f(-1.0f,  1.0f, -1.0f); 
	glVertex3f( 1.0f,  1.0f, -1.0f); 
	glEnd(); 
	
	glColor3f(0.0f, 0.0f, 1.0f); 
	glBegin(GL_QUADS);  //cara lateral izq 
	glVertex3f(-1.0f, -1.0f, -1.0f); 
	glVertex3f(-1.0f, -1.0f,  1.0f); 
	glVertex3f(-1.0f,  1.0f,  1.0f); 
	glVertex3f(-1.0f,  1.0f, -1.0f); 
	glEnd();
	glColor3f(1.0f, 1.0f, 0.0f); 
	glBegin(GL_QUADS);  //cara lateral dcha 
	glVertex3f( 1.0f, -1.0f,  1.0f); 
	glVertex3f( 1.0f, -1.0f, -1.0f); 
	glVertex3f( 1.0f,  1.0f, -1.0f); 
	glVertex3f( 1.0f,  1.0f,  1.0f); 
	glEnd(); 
	
	glColor3f(0.0f, 1.0f, 1.0f); 
	glBegin(GL_QUADS);  //cara arriba 
	glVertex3f(-1.0f,  1.0f,  1.0f); 
	glVertex3f( 1.0f,  1.0f,  1.0f); 
	glVertex3f( 1.0f,  1.0f, -1.0f); 
	glVertex3f(-1.0f,  1.0f, -1.0f); 
	glEnd(); 
	
	glColor3f(1.0f, 0.0f, 1.0f); 
	glBegin(GL_QUADS);  //cara abajo 
	glVertex3f( 1.0f, -1.0f, -1.0f); 
	glVertex3f( 1.0f, -1.0f,  1.0f); 
	glVertex3f(-1.0f, -1.0f,  1.0f); 
	glVertex3f(-1.0f, -1.0f, -1.0f); 
	glEnd(); 
	
} 

void display() { 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glLoadIdentity(); 
	
	glTranslatef(0.0f, 0.0f, -5.0f); 
	
	glRotatef(anguloCuboX, 1.0f, 0.0f, 0.0f); 
	glRotatef(anguloCuboY, 0.0f, 1.0f, 0.0f);
	glutWireTeapot(1.5f);
	
	glLoadIdentity(); 
	
	glTranslatef(0.0f, 0.0f, -5.0f); 
	glRotatef(anguloEsfera, 0.0f, 1.0f, 0.0f); 
	glTranslatef(3.0f, 0.0f, 0.0f); 
	
	glColor3f(1.0f, 1.0f, 1.0f); 
	//drawCube(); 
	
	glFlush(); 
	glutSwapBuffers(); 
	
	// ángulos de rotación automática
	//anguloCuboX+=0.1f; 
	//anguloCuboY+=0.1f; 
	//anguloEsfera+=0.2f; 
} 

void init() { 
	glClearColor(0,0,0,0); 
	glEnable(GL_DEPTH_TEST); 
	ancho = 400; 
	alto = 400; 
} 

void idle() { 
	display(); 
} 

void keyboard(unsigned char key, int x, int y) { 
	switch(key) {
		// Modificaciones de proyección ortogonal
		case 'i': leftOrtho -= 0.1f; break;
		case 'd': rightOrtho += 0.1f; break;
		case 'a': bottomOrtho -= 0.1f; break;
		case 'u': topOrtho += 0.1f; break;
		
		// Modificaciones de Znear 
		case 'n':
			if (hazPerspectiva == 1) {
				zNearPersp -= 0.1f;
			} else {
				zNearOrtho -= 0.1f;
			}
			break;
		case 'N':
			if (hazPerspectiva == 1) {
				zNearPersp += 0.1f;
			} else {
				zNearOrtho += 0.1f;
			}
			break;
		
		// Modificaciones de Zfar 
		case 'f':
			if( hazPerspectiva == 1) {
				zFarPersp -= 0.1f;
			} else {
				zFarOrtho -= 0.1f;
			}
			break;
			
		case 'F': 
			if (hazPerspectiva == 1) {
				zFarPersp += 0.1f;
			} else {
				zFarOrtho += 0.1f;
			}
			break;
		
		// Modificaciones de proyección perspectiva
		case 'b': fov -= 0.1f; break;
		case 'B': fov += 0.1f; break;
		
		// Cambiar entre perspectiva y ortogonal
		case 'p': 
		case 'P': 
			hazPerspectiva = 1; 
			reshape(ancho, alto); 
			break; 
			
		case 'o': 
		case 'O': 
			hazPerspectiva = 0; 
			reshape(ancho, alto); 
			break; 
			
		case 27:   // escape 
			exit(0); 
			break; 
	}
	reshape(ancho, alto);
	glutPostRedisplay();
}

int main(int argc, char **argv) { 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(ancho, alto); 
	glutCreateWindow("Cubo 1"); 
	init(); 
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutIdleFunc(idle); 
	glutKeyboardFunc(keyboard); 
	glutMainLoop(); 
	return 0; 
}
