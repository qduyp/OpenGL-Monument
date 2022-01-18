#include "libs/includes.h"

GLuint VAOs[NumVAOs];
GLuint VBO, EBO, Texture[4];

void generateCube()
{
	glGenVertexArrays(NumVAOs,VAOs);
	glBindVertexArray(VAOs[Cube]);

	GLfloat CubeVertices[] = {0.7,-0.6,0.0,      1.0,1.0,       1.0,0.0,1.0,
							  0.0,-0.6,0.0,      0.0,1.0,       1.0,0.0,1.0,
							  0.0,-0.6,0.5,      1.0,0.0,       1.0,0.0,1.0,
							  0.7,-0.6,0.5,      0.0,0.0,       1.0,0.0,1.0,


							  0.0,-0.1,0.0,      1.0,0.0,       1.0,0.0,1.0,
							  0.7,-0.1,0.0,      0.0,0.0,       1.0,0.0,1.0,
							  0.7,-0.1,0.5,      1.0,1.0,       1.0,0.0,1.0,
							  0.0,-0.1,0.5,      0.0,1.0,       1.0,0.0,1.0,


							  0.0,-0.1,0.5,      0.0,1.0,       1.0,0.0,1.0,
							  0.7,-0.1,0.5,      1.0,1.0,       1.0,0.0,1.0,
							  0.7,-0.6,0.5,      1.0,0.0,       1.0,0.0,1.0,
							  0.0,-0.6,0.5,      0.0,0.0,       1.0,0.0,1.0,


							  0.7,-0.1,0.0,      1.0,0.0,       1.0,0.0,1.0,
							  0.0,-0.1,0.0,      0.0,0.0,       1.0,0.0,1.0,
							  0.0,-0.6,0.0,      0.0,1.0,       1.0,0.0,1.0,
							  0.7,-0.6,0.0,      1.0,1.0,       1.0,0.0,1.0,


							  0.7,-0.1,0.5,      1.0,1.0,       1.0,0.0,1.0,
							  0.7,-0.1,0.0,      0.0,0.0,       1.0,0.0,1.0,
							  0.7,-0.6,0.0,      0.0,1.0,       1.0,0.0,1.0,
							  0.7,-0.6,0.5,      1.0,0.0,       1.0,0.0,1.0,

							  0.0,-0.1,0.0,      0.0,1.0,       1.0,0.0,1.0,
							  0.0,-0.1,0.5,      1.0,0.0,       1.0,0.0,1.0,
							  0.0,-0.6,0.5,      1.0,1.0,       1.0,0.0,1.0,
							  0.0,-0.6,0.0,      0.0,0.0,       1.0,0.0,1.0};

	GLushort CubeIndices[] = {0,1,2,3,
							  4,5,6,7,
							  8,9,10,11,
							  12,13,14,15,
							  16,17,18,19,
							  20,21,22,23};

	/*glGenTextures(1,Texture);
	glBindTexture(GL_TEXTURE_2D,Texture[1]);

	FreeImage_Initialise(TRUE);
	FIBITMAP *bitmapData;
	int imgH, imgW;
	BYTE *bitmapBits;
	FREE_IMAGE_FORMAT bitmapFormat=FIF_UNKNOWN;

	bitmapFormat    =FreeImage_GetFileType("src/Texture/2.jpeg");
	bitmapData      =FreeImage_Load(bitmapFormat,"src/Texture/2.jpeg");
	imgH            =FreeImage_GetHeight(bitmapData);
	imgW            =FreeImage_GetWidth(bitmapData);
	bitmapBits      =FreeImage_GetBits(bitmapData);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgW, imgH, 0, GL_BGR, GL_UNSIGNED_BYTE, bitmapBits);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_WRAP_BORDER,GL_REPEAT);
	FreeImage_Unload(bitmapData);
	glBindTexture(GL_TEXTURE_2D,Texture[1]);*/

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(CubeVertices),CubeVertices,GL_STATIC_DRAW);
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(CubeIndices),CubeIndices,GL_STATIC_DRAW);

	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition,3,GL_FLOAT,GL_FALSE,8*sizeof(float),0);
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(vTexture);
	glVertexAttribPointer(vTexture,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(5*sizeof(float)));
}

void drawCube()
{
	generateCube();
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
}
