#include "libs/includes.h"

void generateTetra()
{
	glGenVertexArrays(NumVAOs,VAOs);
	glBindVertexArray(VAOs[Tetra]);

	GLfloat TetraVertices[]= {0,0,0,			1,0,	0,-1,0,
							  -0.4,0,0,			0,0,	0,-1,0, 
							  -0.2,0,0.35,		0,1,	0,-1,0,
	
							  0,0,0, 			1,0,	0,0.048,-0.16,
							  -0.2,0.4,0.12, 	1,1,	0,0.048,-0.16,
							  -0.4,0,0, 		0,0,	0,0.048,-0.16,
	
							  0,0,0,			1,0,	0.14,0.046,0.08,
							  -0.2,0,0.35,		0,1,	0.14,0.046,0.08,
							  -0.2,0.4,0.12,	1,1,	0.14,0.046,0.08,
	
							  -0.4,0,0,			0,0,	0.14,0.094,-0.08,
							  -0.2,0.4,0.12,	1,1,	0.14,0.094,-0.08,
							  -0.2,0,0.35,		0,1,	0.14,0.094,-0.08};

	glGenTextures(1,Texture);
	glBindTexture(GL_TEXTURE_2D,Texture[0]);

	FreeImage_Initialise(TRUE);
	FIBITMAP *bitmapData;
	int imgH, imgW;
	BYTE *bitmapBits;
	FREE_IMAGE_FORMAT bitmapFormat=FIF_UNKNOWN;

	bitmapFormat    =FreeImage_GetFileType("Texture/1.jpeg");
	bitmapData      =FreeImage_Load(bitmapFormat,"Texture/1.jpeg");

	imgH            =FreeImage_GetHeight(bitmapData);
	imgW            =FreeImage_GetWidth(bitmapData);
	bitmapBits      =FreeImage_GetBits(bitmapData);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgW, imgH, 0, GL_BGR, GL_UNSIGNED_BYTE, bitmapBits);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_WRAP_BORDER,GL_REPEAT);
	FreeImage_Unload(bitmapData);
	glBindTexture(GL_TEXTURE_2D, Texture[0]);


	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(TetraVertices),TetraVertices,GL_STATIC_DRAW);

	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition,3,GL_FLOAT,GL_FALSE,8*sizeof(float),0);
	glEnableVertexAttribArray(vTexture);
	glVertexAttribPointer(vTexture,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(5*sizeof(float)));
}

void drawTetra()
{
	generateTetra();
	glDrawArrays(GL_TRIANGLES,0,12);
}
