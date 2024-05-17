#include <GL/glut.h> 

GLfloat anguloCuboX = 0.0f;  
GLfloat anguloCuboY = 0.0f; 
GLfloat desp = 0.0f; 

GLint ancho, alto; 
int hazPerspectiva = 1; 

void reshape(int width, int height) 
{ 
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	if(hazPerspectiva) 
		gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 
					   20.0f); 
	else 
		glOrtho(-4, 4, -4, 4, 1, 10); 
	
	glMatrixMode(GL_MODELVIEW); 
	
	ancho = width; 
	alto = height; 
} 

void drawCube(void) 
{ 
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

void display() 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(anguloCuboX, 1.0f, 0.0f, 0.0f);
	glRotatef(anguloCuboY, 0.0f, 1.0f, 0.0f); 
	glTranslatef(0.0f, 0.0f, desp);
	drawCube();
	
	glFlush(); 
	glutSwapBuffers(); 
	
} 

void init() 
{ 
	glClearColor(0,0,0,0); 
	glEnable(GL_DEPTH_TEST); 
	ancho = 400; 
	alto = 400; 
} 

void idle() 
{ 
	display(); 
} 

void keyboard(unsigned char key, int x, int y) 
{ 
	switch(key) 
	{ 
	case 'f'://Avanza hacia adelante 5 Unidades de distancia
	case 'F':
		hazPerspectiva=1; 
		reshape(ancho,alto); 
		desp +=0.5f; 
		break;
		
	case 'r'://Gira a la derecha 10 Grados 
	case 'R':
		anguloCuboY+=10.f;
		hazPerspectiva=1; 
		reshape(ancho,alto); 
		break;
	
	case 'l'://Gira a la izquierda 10 Grados
	case 'L':
		anguloCuboY-=10.f;
		hazPerspectiva=1; 
		reshape(ancho,alto); 
		break;
	
	case 'b'://Retrocede 5 Unidades de distancia
	case 'B':
		hazPerspectiva=1; 
		reshape(ancho,alto); 
		desp -=0.5f; 
		break;
		
	case 'u'://Gira hacia arriba 10 Grados 
	case 'U':
		anguloCuboX-=10.f; 
		hazPerspectiva=1; 
		reshape(ancho,alto); 
		break;
	
	case 'd'://Gira hacia abajo 10 Grados
	case 'D':
		anguloCuboX +=10.f; 
		hazPerspectiva=1; 
		reshape(ancho,alto); 
		break;
		
	case 27:   // escape 
		exit(0); 
		break; 
		
	} 
} 

int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
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
