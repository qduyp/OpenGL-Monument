#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>
#include <gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL

enum VAO_IDs {Boden, Pyramid, Tetra, Cube, NumVAOs};
enum Attrib_IDs {vPosition, vColor, vTexture, vNormal};

extern GLuint VAOs[NumVAOs];
extern GLuint VBO, EBO, Texture[2];

void generateBoden();
void drawBoden();
void generateTetra();
void drawTetra();
void generateCube();
void drawCube();
void generatePyramid();
void drawPyramid();
