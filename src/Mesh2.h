//a liberry for cubes


#include <GL/glut.h>
#include <stdio.h>

#include "include/ctypes.h"
#include "include/confing.h"

#include "texture4.h"

static GLfloat vertices[chunkcount*chunkcount*chunkx*chunky*chunkz*4*3];
static GLfloat colors[chunkcount*chunkcount*chunkx*chunky*chunkz*4*3];
static GLfloat texcoords[chunkcount*chunkcount*chunkx*chunky*chunkz*4*3];

static int MeshC = 0; //counter
static int TexC = 0;
static int ColC = 0;



void DrawMesh(vec3f rot){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texName);
	
	glDrawArrays(GL_QUADS,0,MeshC);
	
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void AddMesh(vec2i TexPos,page rect,float hight,int pagetype,bool transparency,vec3i lightlevel){
	
	
	vertices[MeshC++] = rect.p1.x;
	vertices[MeshC++] = rect.p1.y;
	vertices[MeshC++] = rect.p1.z;
	vertices[MeshC++] = rect.p2.x;
	vertices[MeshC++] = rect.p2.y;
	vertices[MeshC++] = rect.p2.z;
	vertices[MeshC++] = rect.p3.x;
	vertices[MeshC++] = rect.p3.y;
	vertices[MeshC++] = rect.p3.z;
	vertices[MeshC++] = rect.p4.x;
	vertices[MeshC++] = rect.p4.y;
	vertices[MeshC++] = rect.p4.z;
	
	for(int i=0;i<4;i++){
		colors[ColC++] = (float)lightlevel.x/16;
		colors[ColC++] = (float)lightlevel.y/16;
		colors[ColC++] = (float)lightlevel.z/16;
		colors[ColC++] = 1;
	}
	

	float Y = ((float)((TexPos.x	)*blockSize)/tarrainImageSize);
	float X = ((float)((TexPos.y	)*blockSize)/tarrainImageSize);
	float H = ((float)((TexPos.x+1)*blockSize)/tarrainImageSize);
	float W = ((float)((TexPos.y+1)*blockSize)/tarrainImageSize);
	
	if((X*16) != W*16-1||Y*16!=H*16-1){printf("X:%f %f %f %f \n",X*16,W*16,Y*16,H*16);}

	texcoords[TexC++] = W;//4
	texcoords[TexC++] = Y;
	texcoords[TexC++] = X;//1
	texcoords[TexC++] = Y;
	texcoords[TexC++] = X;//2
	texcoords[TexC++] = H;
	texcoords[TexC++] = W;//3
	texcoords[TexC++] = H;
}


void AddCubeMesh(blocktype block,vec3f pos,boolcube pages,vec3i lightlevel,bool DisableHeight){
	if(!TransperentTextures){block.transparency=0;}
	if(DisableHeight){block.height=0;}
	if(block.drawtype){
		vec2f img_pos;
		//FRONT
		if(pages.p1){
			AddMesh(block.image[0],cpage(
				cvec3f((float)pos.x,		(float)pos.y,						(float)pos.z+1),
				cvec3f((float)pos.x,		(float)pos.y+1-block.height,	(float)pos.z+1),
				cvec3f((float)pos.x+1,	(float)pos.y+1-block.height,	(float)pos.z+1),
				cvec3f((float)pos.x+1,	(float)pos.y,						(float)pos.z+1)
			),block.height,1,block.transparency,lightlevel);
		}
		
		//LEFT
		if(pages.p2){
			AddMesh(block.image[1],cpage(
				cvec3f((float)pos.x+1,(float)pos.y,						(float)pos.z+1),
				cvec3f((float)pos.x+1,(float)pos.y+1-block.height,	(float)pos.z+1),
				cvec3f((float)pos.x+1,(float)pos.y+1-block.height,	(float)pos.z),
				cvec3f((float)pos.x+1,(float)pos.y,						(float)pos.z)
			),block.height,2,block.transparency,lightlevel);
		}
		//TOP
		if(pages.p3){
			AddMesh(block.image[2],cpage(
				cvec3f((float)pos.x,		(float)pos.y+1-block.height,	(float)pos.z),
				cvec3f((float)pos.x,		(float)pos.y+1-block.height,	(float)pos.z+1),
				cvec3f((float)pos.x+1,	(float)pos.y+1-block.height,	(float)pos.z+1),
				cvec3f((float)pos.x+1,	(float)pos.y+1-block.height,	(float)pos.z)
			),0,3,block.transparency,lightlevel);
			
		}
		//BACK
		if(pages.p4){
			AddMesh(block.image[3],cpage(
				cvec3f((float)pos.x,		(float)pos.y,						(float)pos.z),
				cvec3f((float)pos.x,		(float)pos.y+1-block.height,	(float)pos.z),
				cvec3f((float)pos.x+1,	(float)pos.y+1-block.height,	(float)pos.z),
				cvec3f((float)pos.x+1,	(float)pos.y,						(float)pos.z)
			),block.height,4,block.transparency,lightlevel);
		}
		//RIGHT
		if(pages.p5){
			AddMesh(block.image[4],cpage(
				cvec3f((float)pos.x,(float)pos.y,						(float)pos.z+1),
				cvec3f((float)pos.x,(float)pos.y+1-block.height,	(float)pos.z+1),
				cvec3f((float)pos.x,(float)pos.y+1-block.height,	(float)pos.z),
				cvec3f((float)pos.x,(float)pos.y,						(float)pos.z)
			),block.height,5,block.transparency,lightlevel);
		}
		//BUTTON
		if(pages.p6){
			AddMesh(block.image[5],cpage(
				cvec3f((float)pos.x,		(float)pos.y,(float)pos.z),
				cvec3f((float)pos.x,		(float)pos.y,(float)pos.z+1),
				cvec3f((float)pos.x+1,	(float)pos.y,(float)pos.z+1),
				cvec3f((float)pos.x+1,	(float)pos.y,(float)pos.z)
			),0,6,block.transparency,lightlevel);
		}
		
	}
}
