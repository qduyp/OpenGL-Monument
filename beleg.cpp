//{{{1
//Libs
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>
#include <cmath>
#define GLM_ENABLE_EXPERIMENTAL
using namespace std;
//{{{1
//Main
//{{{2
//vars
GLuint loadShaders(const char* vertexFilePath,
	const char* fragmentFilePath,
 	const char* geometryFilePath,
	const char* tesscontrolFilePath,
	const char* tessevaluationFilePath,
	const char* computeFilePath);
GLint height=100,width=100;
enum VAO_IDs {Sphere,Pyramid,Cuboid,NumVAOs};
enum Buffer_IDs {SphereBuffer,PyramidBuffer,CuboidBuffer,NumBuffer};
enum EBO_IDs {PyramidEBuffer, NumEBuffer};
enum Attrib_IDs {vPosition,vColor};
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint EBuffer[NumEBuffer];
const GLuint NumVertices=60;
const GLuint NumFigure=16;
GLuint program; 
GLuint Location;
GLfloat posx=0.0f;
GLfloat posy=0.0f;
//{{{2
void generatePyramid(){
	static const GLfloat pyramid_pos[] ={
		-1, 0, -1, 1,
		1, 0, -1, 1,
		-1, 0, 1, 1,
		1, 0, 1, 1,
		0, 2, 0, 1
	};
	static const GLfloat pyramid_colors[] ={
		1, 1, 1, 1,
		1, 1, 0, 1,
		1, 0, 1, 1,
		1, 0, 0, 1,
		0, 1, 1, 1
	};
	static const GLushort pyramid_indices[] ={0, 1, 2, 3, 0xFFFF, 1, 3, 4, 2, 0, 4, 1};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffer[PyramidEBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramid_indices), pyramid_indices, GL_STATIC_DRAW);
	glBindVertexArray(VAOs[Pyramid]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PyramidBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_pos) + sizeof(pyramid_colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pyramid_pos), pyramid_pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pyramid_pos), sizeof(pyramid_colors), pyramid_colors);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(pyramid_colors));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
//{{{2
void reshape(int w, int h) {
  	width=w;
  	height=h; 
}
//{{{2
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512,512);
	glutInitContextVersion(3,1);  // (4,2) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	 //GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow(argv[0]);
	glewExperimental=GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	//glutMouseFunc(OnMouseClick);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
}
