#include "confing.h"
#include "ctypes.h"
#include <math.h>
#include <stdio.h>
//#include "perlin_noise.h"

char get_terrain(vec3i pos,int size,int times,float powfactor){
	return (char)(abs(Octaves(abs(pos.x),abs(pos.z),20,20,1,0)-20)/20%20);
}

int get_biom(vec3i pos){
	return abs((int)Redistribution(abs(pos.x),abs(pos.z),100,100,4,0,0.5))%biomscount;
}

int hill(int x,int y){
	return x+y%chunky;
}

