#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>
#include <gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL

enum VAO_IDs {Cube, Pyramid, NumVAOs};
enum Attrib_IDs {vPosition, vColor, vTexture, vNormal};

extern GLuint VAOs[NumVAOs];
extern GLuint VBO, EBO, Texture[4];

void generateCube();
void drawCube();
void generatePyramid();
void drawPyramid();