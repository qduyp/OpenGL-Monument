#include "libs/includes.h"

using glm::mat4;
using glm::vec3;

GLint height,width;
GLuint program;
GLfloat depth = 3.0, high =0.0,side, lighpos, rota, angle, radius=10.0;
GLuint loadShaders(const char* vertexFilePath,
				   const char* fragmentFilePath,
     			   const char* geometryFilePath,
     			   const char* tesscontrolFilePath,
     			   const char* tessevaluationFilePath,
     			   const char* computeFilePath);

void init(){
    program  = loadShaders("src/Shader/Dreiecke.vs", "src/Shader/Dreiecke.fs", "", "", "", "");
    glUseProgram(program);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
}

void display(){
	glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST_BUFFER );
    glViewport(0, height/2, width/2, height/2);
    vec3 cameraPos = vec3(side, high, depth);
    vec3 cameraFront = vec3(rota,0.0,-1.0);
    mat4 Translation = glm::translate(mat4(1.0),vec3(0.15,0.25,0.6));
	mat4 Scale = glm::scale(vec3(0.5,0.5,0.5));
    mat4 Model = glm::rotate(Translation*Scale,angle,vec3(1.0,0.0,0.0));
    mat4 View  = glm::lookAt(cameraPos,cameraPos+cameraFront,vec3(0.0,1.0,0.0));
    mat4 Projection = glm::perspective(120.0f,1.0f,0.1f,10.0f);
    mat4 ModelViewProjection = Projection * View * Model;
    GLuint locFinal = glGetUniformLocation(program,"ModelViewProjection");
    glUniformMatrix4fv(locFinal,1,GL_FALSE,&ModelViewProjection[0][0]);
    GLuint locModel = glGetUniformLocation(program,"Model");
    glUniformMatrix4fv(locModel,1,GL_FALSE,&Model[0][0]);
    vec3 lightPos = vec3(-1.5,0.0,0.0);
    vec3 lightColor = vec3(1.0,1.0,1.0);
    GLuint loclightPos = glGetUniformLocation(program,"lightPos");
    glUniform3fv(loclightPos,1,&lightPos[0]);
    GLuint loclightColor = glGetUniformLocation(program,"lightColor");
    glUniform3fv(loclightColor,1,&lightColor[0]);
    GLuint loccameraPos = glGetUniformLocation(program,"viewPos");
    glUniform3fv(loccameraPos,1,&cameraPos[0]);
    drawPyramid();
    Translation = glm::translate(mat4(1.0),vec3(0.15,0.15,0.6));
    Model = glm::rotate(Translation,angle,vec3(1.0,1.0,1.0));;
    ModelViewProjection = Projection * View * Model;
    glUniformMatrix4fv(locFinal,1,GL_FALSE,&ModelViewProjection[0][0]);
    drawCube();
    glViewport(width/2,height/2,width/2,height/2);
    View  = lookAt(vec3(0.0,0.0,3.0),vec3(0.0,0.0,2.0),vec3(0.0,1.0,0.0));
    Model = Scale;
    ModelViewProjection = Projection * View * Model;
    glUniformMatrix4fv(locFinal,1,GL_FALSE,&ModelViewProjection[0][0]);
    drawCube();
    drawPyramid();
    glViewport(0,0,width/2,height/2);
    View  = lookAt(vec3(0.0,3.0,0.0),vec3(0.0,2.0,0.0),vec3(1.0,0.0,0.0));
    Model = Scale;
    ModelViewProjection = Projection * View * Model;
    glUniformMatrix4fv(locFinal,1,GL_FALSE,&ModelViewProjection[0][0]);
    drawCube();
    drawPyramid();
    glViewport(width/2,0,width/2,height/2);
    View  = lookAt(vec3(3.0,0.0,0.0),vec3(2.0,0.0,0.0),vec3(0.0,1.0,0.0));
    Model = Scale;
    ModelViewProjection = Projection * View * Model;
    glUniformMatrix4fv(locFinal,1,GL_FALSE,&ModelViewProjection[0][0]);
    drawCube();
    drawPyramid();
    glutSwapBuffers();
    angle+=0.1;
}

void reshape(int w, int h){
    glViewport(0,0,w,h);
}

void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(10,timer,0);
}

void keyboard(unsigned char theKey, int mouseX, int mouseY){
  switch (theKey){
        case 'w':
		   	depth-= 0.25; 
			break;
        case 's':
		   	depth+=0.25; 
			break;
        case 'a':
		   	side+=0.25;
			break;
        case 'd':
		   	side-=0.25;
			break;
        case 'h':
		   	high-=0.25;
			break;
        case 'l':
		   	high+=0.25;
			break;
        case 'j':
		   	rota-= 0.25; 
			break;
        case 'k':
		   	rota+= 0.25;
			break;
        case 'q':
		   	exit(0);
    }
}

int main(int argc, char** argv){
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
