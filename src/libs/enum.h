#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <unistd.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/matrix_transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>
#define GLM_ENABLE_EXPERIMENTAL

//enum VAO_IDs {Cube, Sphere, Kegel, NumVAOs};
enum VAO_IDs {Cube, NumVAOs};
enum Attrib_IDs {vPosition,vColor};
