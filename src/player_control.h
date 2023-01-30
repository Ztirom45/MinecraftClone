#include <math.h>

#include "include/lower.h"
#include "include/ctypes.h"
//#include "include/vec.h"

#define MB_LEFT   0
#define MB_MIDDLE 1
#define MB_RIGHT  2
#define LMB_PRESSED (1<<0)
#define MMB_PRESSED (1<<1)
#define RMB_PRESSED (1<<2)
#define LMB_CLICKED (1<<16)
#define MMB_CLICKED (1<<17)
#define RMB_CLICKED (1<<18)
#define MB_PRESSED(state, button) (1<<(button))
#define MB_CLICKED(state, button) (1<<((button)+16)))
#define MB_MASK_PRESSED 0x0000ffffL
#define MB_MASK_CLICKED 0xffff0000L

#define KEY_SHIFT 112
//player Var
static vec3f player = {0,-70,0};
static double rotate_x = 0;
static double rotate_y = 0;

static float speed = 0.1;  //movement speed
static float relspeed = 0.05; //mouse speed
//keys
static bool presskeys[265];
static bool shift_press = 0;
static bool place_bool = 0;
//window
static int w;
static int h;





void move(float angley,float steps){
	vec3f playeraddy = rotateY(cvec3f(speed,0,0),angley);
	player.x -= playeraddy.x;
	player.z += playeraddy.z;
}

//move player
void playercontrol() {
	if(presskeys[*"w"]||presskeys[*"W"]){move(rotate_y-90,speed);}
	if(presskeys[*"s"]||presskeys[*"S"]){move(rotate_y+90,speed);}
	if(presskeys[*"a"]||presskeys[*"A"]){move(rotate_y+180,speed);}
	if(presskeys[*"d"]||presskeys[*"D"]){move(rotate_y,speed);} 
	if(presskeys[*"e"]){place_bool = 1;}else{place_bool=0;} 
	
	if(presskeys[*" "]){player.y -= speed;}
	if(presskeys[*"\t"]){player.y += speed;}
}

//key values
void NKeys(unsigned char key, int x, int y) {
	//printf("Nkey:%d\n",key);
	glutWarpPointer(w/2, h/2);
	presskeys[lower(key)] = 1;
	if(lower(key) == *"q"){exit(0);}
}
//secial key values
void NKeysUP(unsigned char key, int x, int y) {
	presskeys[lower(key)] = 0;
	//printf("Nupkey:%d\n",key);
}

void specialKeys( int key, int x, int y ) {
	//printf("key:%d\n",key);
	if(key = KEY_SHIFT){shift_press=1;}
}
void specialKeysUP(unsigned char key, int x, int y){
	//printf("keyup:%d\n",key);
	if(key = KEY_SHIFT){shift_press=0;}
}

void mouse(int x,int y){
	if(x!=w/2&&y!=h/2){//if curser != 0 0
		glutWarpPointer(w/2, h/2);//set curser pos
		glutSetCursor(GLUT_CURSOR_NONE);//hide curser
		rotate_y += (x-w/2)*relspeed;//get y
		float xrot = (y-h/2)*relspeed; //we need x_Rot because of the Player cant tur his head infintly about X
		if((rotate_x<90 || xrot < 0)&&(rotate_x>-90 || xrot > 0)){rotate_x += xrot;}//write y
		if(rotate_y>360){rotate_y-=360;}
	}
}


