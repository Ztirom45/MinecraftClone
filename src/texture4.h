#include <GL/glut.h>


#include <stdio.h>
#include <stdlib.h>
#include <png.h>



#include "include/ctypes.h"
#include "include/blocks.h"
#include "include/confing.h"

#include "include/ztpng.h"

//gl texture
static GLuint texName;


GLuint load_texture(){
	load_row_pointers();
	//glut image
	GLuint texTure = 0;
	glGenTextures(1, &texTure);
	glBindTexture(GL_TEXTURE_2D, texTure);
	
	//texture cord up to 0 and 1
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	//scale filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	
	//gen image
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pixel_array_w,pixel_array_h,0,GL_RGBA,GL_UNSIGNED_BYTE,pixel_array);
   return texTure;
}


void setup_texture(){
	//char * FileName = "images/terrain.png";
	glEnable(GL_COLOR);
	glColor4f(0,0,0,0);
	glDisable(GL_COLOR);
	glEnable(GL_TEXTURE_2D);
	
	
	texName = load_texture();
	
	
	//load_texture(cvec2i(0*terrain_width,0*terrain_Height),cvec2i(0*terrain_width+16,0*terrain_Height+16));//memory errors
	
	
	glDisable(GL_TEXTURE_2D);
}


void draw_texture(GLuint Texture,page rect,float hight,bool transp,vec3i LightLevel){
	//Enable
	//transp = 1; //bad performence
	//glPushMatrix();
	if(transp){
		
		//printf("%f\n",hight);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
		glEnable(GL_ALPHA_TEST);
		glColor4f(	(float)LightLevel.x/LightLevelSize,
						(float)LightLevel.y/LightLevelSize,
						(float)LightLevel.z/LightLevelSize,1);//Replace this alpha for transparency
	}else{
		glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glColor4f(	(float)LightLevel.x/LightLevelSize,
						(float)LightLevel.y/LightLevelSize,
						(float)LightLevel.z/LightLevelSize,0);
	}
	glBegin(GL_QUADS);
	
	//draw
	
	glTexCoord2f((float)1-hight,0);	glVertex3f(rect.p1.x,rect.p1.y,rect.p1.z);
	glTexCoord2f(0,0);					glVertex3f(rect.p2.x,rect.p2.y,rect.p2.z);
	glTexCoord2f(0,1);					glVertex3f(rect.p3.x,rect.p3.y,rect.p3.z);
	glTexCoord2f((float)1-hight,1);	glVertex3f(rect.p4.x,rect.p4.y,rect.p4.z);
	//disable
	glEnd();
	if(transp){
		glDisable(GL_BLEND); 
	}
	//glPopMatrix();
}
