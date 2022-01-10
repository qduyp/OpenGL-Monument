#include "libs/cube.h"
//GLuint VAOs[NumVAOs];
//GLuint program;

using glm::mat4;
using glm::vec3;

void generateCube()
{
//Vertex Data
    GLfloat CubeVertices[] = {-0.5,-0.5,-0.5,1.0,
                              -0.5,-0.5, 0.0,1.0,
                              -0.5, 0.5,-0.5,1.0,
                              -0.5, 0.5, 0.0,1.0,
                               0.5,-0.5,-0.5,1.0,
                               0.5,-0.5, 0.0,1.0,
                               0.5, 0.5,-0.5,1.0,
                               0.5, 0.5, 0.0,1.0};
    GLfloat CubeColors[] = {1.0,1.0,1.0,1.0,
                            1.0,1.0,0.0,1.0,
                            1.0,0.0,1.0,1.0,
                            1.0,0.0,0.0,1.0,
                            0.0,1.0,1.0,1.0,
                            0.0,1.0,0.0,1.0,
                            0.0,0.0,1.0,1.0,
                            0.5,0.5,0.5,1.0};
    GLushort CubeIndices[] = {0,1,2,3,6,7,4,5,0xFFFF,2,6,0,4,1,5,3,7};



//Genertate Vertex Array
    glGenVertexArrays(NumVAOs,VAOs);
    glBindVertexArray(VAOs[Cube]);

//Genertate Vertex Buffer
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices)+sizeof(CubeColors), CubeVertices, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(CubeVertices), CubeVertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(CubeVertices), sizeof(CubeColors), CubeColors);

//Activate Attribute Pointer
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(CubeVertices));

    //Generate Element Buffer
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(CubeIndices),CubeIndices,GL_STATIC_DRAW);
}

void drawCube()
{
    generateCube();
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(0xFFFF);

    mat4 Translate = glm::translate(mat4(1.0f),vec3(-0.7f,-0.7f,-3.0f));
    mat4 Projection= //glm::ortho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
                        glm::perspective(100.0f,1.0f,0.1f,10.0f);
    mat4 Rotate    = glm::rotate(mat4(1.0f),angle,vec3(1.0,1.0,1.0));
    mat4 Scale     = glm::scale(mat4(1.0f),vec3(0.0,0.0,0.0));
    mat4 FinalMat  = Projection*Translate*Rotate;
    //mat4 FinalMat = mat4(1.0f);
    GLuint Location= glGetUniformLocation(program,"FinalMat");
    glUniformMatrix4fv(Location, 1, GL_FALSE, &FinalMat[0][0]);
    glDrawElements(GL_TRIANGLE_STRIP,17,GL_UNSIGNED_SHORT,0);
    angle+=0.005;
}
