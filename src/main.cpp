#include "libs/cube.h"

GLuint loadShaders(const char* vertexFilePath,
				   const char* fragmentFilePath,
 				   const char* geometryFilePath,
				   const char* tesscontrolFilePath,
				   const char* tessevaluationFilePath,
				   const char* computeFilePath);
GLint height=100,width=100;
GLuint VAOs[NumVAOs];
GLuint EBO, VBO;
GLuint program; 
GLfloat angle=45.0f;
//GLuint Location;

void init(){
	program = loadShaders("src/Shader/beleg.vs", "src/Shader/beleg.fs", "", "", "", "");
	glUseProgram(program);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//drawKegel();
	drawCube();
	//drawSphere();
	glutSwapBuffers();
}

void reshape(int w, int  h){
	glViewport(0, 0, w, h);
}

void timer(int t){
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(1024, 1024);
	glutCreateWindow("Monument");
	glewExperimental=GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	//glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	timer(0);
	glutMainLoop();
}
