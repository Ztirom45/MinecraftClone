//TODO:

//compile Linux: g++ main.cpp -o out -I /usr/include -lGL -lglut -lGLU -lGLEW -LGLEXT
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

//libberrys
#include "include/perlin_noise.h"
#include "include/world_gen.h"

//functions

#include "player_control.h"
#include "chunks4.h"//mesh/texture //downgrade to run stable


vec3f turn(vec3f point,int angle){
	vec3f result = {0,0,0};
	result.x = cos((angle)/180*pi);
	result.y = sin((angle)/180*pi);
	return result;
}

#define CubeArraySize 4

static int FOW = 300;
static time_t sec;
static int fps = 0;

//block place vars:

static vec3f addangle;
static vec3f cube_pos;
static vec3f vec_save;
static chunktype cube_pos_chunk;
static chunktype cube_pos_save;
static bool find_block = false;
static bool buttontoggle = true;



void place_block(){
	find_block = false;
	for(int i=0;i<10;i++){
		addangle = RotatePlayerDistance(i,cvec3f(rotate_x,rotate_y,0));
		cube_pos = cvec3f((int)(addangle.x-player.x),
						(int)(addangle.y-player.y),
						(int)(addangle.z-player.z));
		cube_pos_chunk = vec3f2chunktype(cube_pos,chunkUp.x,chunkUp.y);
	
		
		if(	mychunk[cube_pos_chunk.cx][cube_pos_chunk.cz] [cube_pos_chunk.x][cube_pos_chunk.y][cube_pos_chunk.z] != 0 &&
			mychunk[cube_pos_chunk.cx][cube_pos_chunk.cz] [cube_pos_chunk.x][cube_pos_chunk.y][cube_pos_chunk.z] != 7){
			find_block = true;break;
		}else{
			cube_pos_save = cube_pos_chunk;vec_save=cube_pos;}
	}
	if(cube_pos_chunk.y < chunky && cube_pos_chunk.y > 0 && find_block){
		
		
		mychunk[cube_pos_save.cx][cube_pos_save.cz][cube_pos_save.x][cube_pos_save.y][cube_pos_save.z] = 8;
		SetupMesh();
	}
}

void remove_block(){
	find_block = false;
	for(int i=0;i<20;i++){
		addangle = RotatePlayerDistance(i,cvec3f(rotate_x,rotate_y,0));
		cube_pos = cvec3f((int)(addangle.x-player.x),
						(int)(addangle.y-player.y),
						(int)(addangle.z-player.z));
		cube_pos_chunk = vec3f2chunktype(cube_pos,chunkUp.x,chunkUp.y);
		//mychunk[cube_pos_chunk.cx][cube_pos_chunk.cz][cube_pos_chunk.x][cube_pos_chunk.y][cube_pos_chunk.z] = 0;
		
		if(	mychunk[cube_pos_chunk.cx][cube_pos_chunk.cz] [cube_pos_chunk.x][cube_pos_chunk.y][cube_pos_chunk.z] != 0 && 
			mychunk[cube_pos_chunk.cx][cube_pos_chunk.cz] [cube_pos_chunk.x][cube_pos_chunk.y][cube_pos_chunk.z] != 7){
			find_block = true;
			break;
		}else{
			vec_save=cube_pos;
		}
	}
	if(cube_pos_chunk.y < chunky && cube_pos_chunk.y > 0 && find_block){
		mychunk[cube_pos_chunk.cx][cube_pos_chunk.cz][cube_pos_chunk.x][cube_pos_chunk.y][cube_pos_chunk.z] = 0;
		SetupMesh();
	}
}


void MouseButton(int button, int state, int x, int y)
{
	if(buttontoggle){
		
		switch(button){
			case GLUT_LEFT_BUTTON:remove_block();break;
			//case GLUT_MIDDLE_BUTTON:
			case GLUT_RIGHT_BUTTON:place_block();break;
		};
		buttontoggle = false;
	}else{buttontoggle=true;}
}

void display()
{
	sec = time(NULL);
	chunk_update();
	playercontrol();
	
	//3d stuff
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	w = glutGet( GLUT_WINDOW_WIDTH );//window wight
	h = glutGet( GLUT_WINDOW_HEIGHT );//window hight
	
	//water
	/*
	if(mychunk[1][1][-(int)player.x+1][-(int)player.y+1][-(int)player.z+1]==7){
		glClearColor(0, 0,1,1);
		FOW=100;
	}else{
		glClearColor(0.5, 1,0.99,1);
		FOW = 100;
	}
	*/
	glClearColor(0.5, 1,0.99,1);
	gluPerspective( 60, w / h, 0.1, FOW );
	glMatrixMode( GL_MODELVIEW );//set mod
	glLoadIdentity();//LOAD matrix
	
	//rotate
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 1.0, 0.0 );
	glTranslatef(player.x, player.y, player.z);
	
	//printf("a:%d\n",time(NULL)-sec);
	//draw stuff
	glEnable(GL_TEXTURE_2D);
	DrawMesh(cvec3f(rotate_x,rotate_y,0));
	
	//printf("b:%d\n",time(NULL)-sec);
	//place_block(0);
	
	//Setup for 2D
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, w, h, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);
	
	//draw cross
	glBegin(GL_QUADS);
		 glColor3f(1.0f, 1.0f, 1.0);
		 glVertex2f(w/2-2,h/2-2);
		 glVertex2f(w/2+2,h/2-2);
		 glVertex2f(w/2+2,h/2+2);
		 glVertex2f(w/2-2,h/2+2);
	glEnd();

	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	

	//swap buffers while
	glutSwapBuffers();
	glutPostRedisplay();
	if(time(NULL) != sec){
		printf("Fps:%d\n",fps);
		fps = 0;
	}else{
		fps++;
	}
	//printf("c:%d\n",time(NULL)-sec);
}


int main( int argc, char **argv ){
	//init
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitWindowSize( 1000, 1000 );
	glutInitWindowPosition( 300, 0 );
	
	
	//window
	glutCreateWindow( "ztcraft" );
	//glutFullScreen();
	glutDisplayFunc( display );

	//controll
	glutSpecialFunc( specialKeys );
	glutKeyboardUpFunc(specialKeysUP);
	glutKeyboardFunc(NKeys);
	glutKeyboardUpFunc(NKeysUP);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(MouseButton);

	//enable
	glEnable( GL_DEPTH_TEST );
	//glEnable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//grafical pointer
	glVertexPointer(3,GL_FLOAT,0,vertices);
	glColorPointer	(4,GL_FLOAT,0,colors);
	glTexCoordPointer	(2,GL_FLOAT,0,texcoords);

	//setup game
	setup_texture();
	setup_chunks();
	SetupMesh();
	glutMainLoop();
	return 0;
}
