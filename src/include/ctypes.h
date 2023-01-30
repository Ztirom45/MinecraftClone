
#ifndef types_include
	#include "cvec.h"
	#include "confing.h"
	#include <stdbool.h>
	
	#define types_include
	//pixel types
	

	typedef struct _page{
		vec3f p1;
		vec3f p2;
		vec3f p3;
		vec3f p4;
	}page;

	typedef struct _vectorpage{
		vec3i p1;
		vec3i p2;
		vec3i p3;
		vec3i p4;
	}vectorpage;
	
	typedef struct _boolcube{
		bool p1;
		bool p2;
		bool p3;
		bool p4;
		bool p5;
		bool p6;
	}boolcube;

	typedef struct _intcube{
		char p1;
		char p2;
		char p3;
		char p4;
		char p5;
		char p6;
	}intcube;

	typedef struct _pointcube{
		vec2i p1;
		vec2i p2;
		vec2i p3;
		vec2i p4;
		vec2i p5;
		vec2i p6;
	} pointcube;

	typedef struct _chunktype{
		int cx;
		int cz;
		int x;
		int y;
		int z;
	}chunktype;


page cpage(vec3f p1,vec3f p2,vec3f p3,vec3f p4){
	page v = {p1,p2,p3,p4};
	return v;
}


chunktype cchunktype(int cx,int cz,int x,int y,int z){
	chunktype v = {cx,cz,x,y,z};
	return v;
}

boolcube cboolcube(bool p1,bool p2,bool p3,bool p4,bool p5,bool p6){
	boolcube v = {p1,p2,p3,p4,p5,p6};
	return v;
}
	
boolcube andcube(boolcube c1,boolcube c2){
	return cboolcube(	c1.p1 && c2.p1,
							c1.p2 && c2.p2,
							c1.p3 && c2.p3,
							c1.p4 && c2.p4,
							c1.p5 && c2.p5,
							c1.p6 && c2.p6);
}

boolcube orcube(boolcube c1,boolcube c2){
	return cboolcube(	c1.p1 || c2.p1,
							c1.p2 || c2.p2,
							c1.p3 || c2.p3,
							c1.p4 || c2.p4,
							c1.p5 || c2.p5,
							c1.p6 || c2.p6);
}
	
boolcube ZCube(vec3f angle){
	
	
	boolcube result = {1,1,1,1,1,1};
	/*
	printf("a:%f\n",rotate(cvec3f( 0, 0, 1),angle).z);
	printf("a:%f\n",rotate(cvec3f( 1, 0, 0),angle).z);
	printf("a:%f\n",rotate(cvec3f( 0, 1, 0),angle).z);
	printf("a:%f\n",rotate(cvec3f( 0, 0, -1),angle).z);
	printf("a:%f\n",rotate(cvec3f( -1, 0, 0),angle).z);
	printf("a:%f\n",rotate(cvec3f( 0, -1, 0),angle).z);
	printf("\n");
	*/
	
	result.p1 = rotate(cvec3f( 0, 0, 1),angle).z>-0.6;//Front
	//result.p2 = rotate(cvec3f( 1, 0, 0),angle).z>-0.6;//Left  error 
	//result.p3 = rotate(cvec3f( 0, 1, 0),angle).z>-0.6;//Top eror 
	result.p4 = rotate(cvec3f( 0, 0,-1),angle).z>-0.6;//Back
	//result.p5 = rotate(cvec3f(-1, 0, 0),angle).z>-0.6;//Right eror 
	result.p6 = rotate(cvec3f( 0, -1, 0),angle).z>-0.6;//Down
	
	return result;
}
	
	
	
	vec3i chunktype2vec3i(chunktype chunkpos,int chunkUpX,int chunkUpZ){
		//cx chunk cord chunkUpx player/chunksize chunkx = sizechunk x = pos chunk
		vec3i ret;
		ret.x = (int)((chunkpos.cx-chunkUpX))*chunkx+chunkpos.x;
		ret.y = (int)chunkpos.y;
		ret.z = (int)((chunkpos.cz-chunkUpZ))*chunkz+chunkpos.z;
		return ret;
	}
	
	chunktype vec3f2chunktype(vec3f pos,int chunkUpX,int chunkUpZ){
		int x = round(pos.x + chunkUpX*chunkx);//((int)((player.x+1)/chunkx))*chunkx;
		int y = round(pos.y+1);
		int z = round(pos.z + chunkUpZ*chunkz);//((int)((player.z+1)/chunkz))*chunkz;
		int cx = -chunkcountmin +(int)(x/chunkx)-(x<0);
		int cz = -chunkcountmin +(int)(z/chunkz)-(z<0);
		x = x-(int)(x/chunkx)*chunkx+(chunkx*(x<0))+1;
		z = z-(int)(z/chunkz)*chunkz+(chunkz*(z<0))+1;
		return cchunktype(cx,cz,x,y,z);
	}

#endif

