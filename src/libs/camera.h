#ifndef CAMERA_H
#define CAMERA_H

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

using glm::mat4;
using glm::vec3;

class camera{
	public:
		GLfloat depth = 3.0, high =0.0,side, lighpos, rota, angle;
}
