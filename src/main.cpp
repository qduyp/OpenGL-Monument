#include "libs/includes.h"

using glm::mat4;
using glm::vec3;

GLint height,width;
GLuint program;
GLuint VAOs[NumVAOs];
GLuint VBO, Texture[2];
GLfloat r=1.0f,g=1.0f,b=1.0f;
GLuint loadShaders(const char* vertexFilePath,
				   const char* fragmentFilePath,
				   const char* geometryFilePath,
				   const char* tesscontrolFilePath,
				   const char* tessevaluationFilePath,
				   const char* computeFilePath);

void init()
{
	program  = loadShaders("src/Shader/Dreiecke.vs", "src/Shader/Dreiecke.fs", "", "", "", "");
	glUseProgram(program);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_COLOR_MATERIAL);
}

void display()
{
	vec3 lightLO = vec3(0,0,0);
	vec3 ambientColor = vec3(1.0f,1.0f,1.0f);
	vec3 diffuseColor = vec3(1.0f,1.0f,1.0f);
	vec3 specular = vec3(1.0f,1.0f,1.0f);

	vec3 MACO = vec3(1,1,1);
	vec3 MDCO = vec3(1,1,1);
	vec3 MSCO = vec3(0.633f, 0.727811f, 0.633f);
	float shiniCO = 0.6f;

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	mat4 View = glm::lookAt(vec3(3,3,3),vec3(0,0,0),vec3(0,1,0));
	mat4 Projection = glm::perspective(120.0f,1.0f,0.1f,10.0f);
	mat4 ModelViewProjection = Projection * View;
	GLuint locFinal =  glGetUniformLocation(program, "ModelViewProjection");
	glUniformMatrix4fv(locFinal,1,GL_FALSE,&ModelViewProjection[0][0]);
	GLuint locLO =  glGetUniformLocation(program, "light.location");
	glUniform3fv(locLO,1,glm::value_ptr(lightLO));
	GLuint locLA =  glGetUniformLocation(program, "light.ambient");
	glUniform3fv(locLA,1,glm::value_ptr(ambientColor));
	GLuint locDI =  glGetUniformLocation(program, "light.diffuse");
	glUniform3fv(locDI,1,glm::value_ptr(diffuseColor));
	GLuint locSP =  glGetUniformLocation(program, "light.specular");
	glUniform3fv(locSP,1,glm::value_ptr(specular));

	GLuint locMAB =  glGetUniformLocation(program, "material.ambient");
	glUniform3fv(locMAB,1,glm::value_ptr(MACO));
	GLuint locMDI =  glGetUniformLocation(program, "material.diffuse");
	glUniform3fv(locMDI,1,glm::value_ptr(MDCO));
	GLuint locMSP =  glGetUniformLocation(program, "material.specular");
	glUniform3fv(locMSP,1,glm::value_ptr(MSCO));
	GLuint locMSH =  glGetUniformLocation(program, "material.shininess");
	glUniform3fv(locMSH,1,&shiniCO);

	GLuint fTT =  glGetUniformLocation(program, "flagTexture");
	glUniform1i(fTT,0);
	drawBoden();
	drawTetra();
	glUniform1i(fTT,1);
	glVertexAttrib3f(vColor,r,g,b);
	drawCube();
	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10,timer,0);
}

void keyboard(unsigned char theKey, int mouseX, int mouseY)
{
	switch (theKey)
	{
	case 'a':
		r=0.078f;
		g=0.0f;
		b=0.567f;
		break;
	case 's':
		break;
	case 'd':
		break;
	case 'h':
		break;
	case 'l':
		break;
	case 'q':
		exit(0);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	height=glutGet(GLUT_SCREEN_HEIGHT);
	width=glutGet(GLUT_SCREEN_WIDTH);
	glutInitWindowSize(width,height);
	glutInitContextVersion(4,5);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutCreateWindow("NOT EXE");
	glewExperimental=GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	glutKeyboardFunc(keyboard);
	timer(0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
}
