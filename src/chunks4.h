//TODO: load chunk into memory;load chunk from memory
//TODO: trees
#include "Mesh2.h"
#include "include/blocks.h"
#include "include/confing.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//min and max
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

static char mychunk[chunkcount][chunkcount][chunkx+2][chunky+2][chunkz+2];

static vec2i chunkUp  = {0,0};//chunkpos
static vec2i chunkOld = {0,0};
static int LightHightMax[chunkcount][chunkcount];//the lowest block in every loaded chunk


static bool FirstFrame = true;

//define biom type
typedef struct _biom{
	int height;
	int size;
	int times;
	float powfactor;
	bool lake;
	bool ice;
	bool snow;
	int blockup;
	int blockmiddle;
	int blockdown;
	int tree;
}biom;

biom cbiom(	int height,int size,int times,float powfactor,bool lake,bool ice,bool snow,
				int blockup,int blockmiddle,int blockdown,int tree){
	biom v = {height,size,times,powfactor,lake,ice,snow,blockup,blockmiddle,blockdown,tree};
	return v;
}
//define all bioms
const biom plains = 			{40,10,1,0,	true,false,false,	1,2,3,1};
const biom snowy_plains =	{42,10,1,0,	true,true,true,	4,2,3,2};
const biom desert =			{43,10,1,0,	false,false,false,9,9,3,3};
const biom mountains = 		{55,10,1,0,	false,false,true,	10,3,3,0};

biom bioms[biomscount] = {plains,snowy_plains,desert,mountains};

const char* cChunkFilename(int x,int y)
{
	static char s[32];
	sprintf(s,CHUNK_PATH,x,y);
	return s;
}

void save_chunk(int cx,int cz,int px,int py){
	const char * path = cChunkFilename(px,py);
	FILE *fp;
	fp = fopen(path, "w+");
	//fp2 = fopen("/home/moritz/Dokumente/c c++/mc_clone/final6/files/chunks/chunkhight", "w+");
	for(int x=0;x<chunkx;x++){//c = counter != chunk
		for(int y=0;y<chunky;y++){
			//fputs(mychunk[cx][cy][x][y],fp);
			
			for(int z=0;z<chunkz;z++){
				fprintf(fp, "%c",mychunk[cx][cz][x+1][y+1][z+1]);
			}
			
		}
	}
	fprintf(fp,"%c",(char)LightHightMax[cx][cz]);
	
	
	fclose(fp);
}

bool load_chunk(int cx,int cz,int px,int py){
	const char * path = cChunkFilename(px,py);
	FILE *fp;
	if (fp = fopen(path, "r")){
		for(int x=0;x<chunkx;x++){//c = counter != chunk
			for(int y=0;y<chunky;y++){
				for(int z=0;z<chunkz;z++){
					mychunk[cx][cz][x+1][y+1][z+1] = fgetc(fp);
				}
			}
		}
		LightHightMax[cx][cz] = fgetc(fp);
		fclose(fp);
		return 1;
	}else{
		return 0;
	}
}

void tree_model(int cx,int cz,int x,int y,int z,int num){
	switch(num){
		case 1:
			if(x>3 && x<14 && z>3 && z<14){
				mychunk[cx][cz][x+1][y	][z+1] = 5;
				mychunk[cx][cz][x+1][y+1][z+1] = 5;
				mychunk[cx][cz][x+1][y+2][z+1] = 5;
				mychunk[cx][cz][x+1][y+3][z+1] = 6;
				mychunk[cx][cz][x+1][y+4][z+1] = 6;
				
				mychunk[cx][cz][x+1][y+3][z  ] = 6;
				mychunk[cx][cz][x  ][y+3][z+1] = 6;
				mychunk[cx][cz][x+2][y+3][z+1] = 6;
				mychunk[cx][cz][x+1][y+3][z+2] = 6;
				
				mychunk[cx][cz][x+1][y+2][z  ] = 6;
				mychunk[cx][cz][x  ][y+2][z+1] = 6;
				mychunk[cx][cz][x+2][y+2][z+1] = 6;
				mychunk[cx][cz][x+1][y+2][z+2] = 6;
			}
			break;
			
		case 2:
			if(x>3 && x<14 && z>3 && z<14){
				mychunk[cx][cz][x+1][y	][z+1] = 5;
				mychunk[cx][cz][x+1][y+1][z+1] = 5;
				mychunk[cx][cz][x+1][y+2][z+1] = 5;
				mychunk[cx][cz][x+1][y+3][z+1] = 6;
				mychunk[cx][cz][x+1][y+4][z+1] = 6;
				mychunk[cx][cz][x+1][y+5][z+1] = 11;
				
				mychunk[cx][cz][x+1][y+3][z  ] = 6;
				mychunk[cx][cz][x  ][y+3][z+1] = 6;
				mychunk[cx][cz][x+2][y+3][z+1] = 6;
				mychunk[cx][cz][x+1][y+3][z+2] = 6;
				
				mychunk[cx][cz][x+1][y+2][z  ] = 6;
				mychunk[cx][cz][x  ][y+2][z+1] = 6;
				mychunk[cx][cz][x+2][y+2][z+1] = 6;
				mychunk[cx][cz][x+1][y+2][z+2] = 6;

				mychunk[cx][cz][x+1][y+4][z  ] = 11;
				mychunk[cx][cz][x  ][y+4][z+1] = 11;
				mychunk[cx][cz][x+2][y+4][z+1] = 11;
				mychunk[cx][cz][x+1][y+4][z+2] = 11;
				
			}
			break;
			
		case 3:
			mychunk[cx][cz][x+1][y][z+1] = 12;
			mychunk[cx][cz][x+1][y+1][z+1] = 12;
			mychunk[cx][cz][x+1][y+2][z+1] = 12;
			break;
	}
}




void setup_chunk(int cx, int cz){
	LightHightMax[cx][cz] = 0;
	int x,y,z,a,hightmap,i,biom_connection,biom_number;
	biom biom_now;
	x = y = z = a = hightmap = i = biom_connection = biom_number = 0;
	
	//tree array
	vec4i trees[85];
	int treecount = 0;
	
	for(x=0;x<chunkx;x++){ 
		for(z=0;z<chunkz;z++){
			//reset
			for(int y=1;y<chunky+2;y++){
				mychunk[cx][cz][x+1][y][z+1] = 0;
			}
			mychunk[cx][cz][x+1][0][z+1] = 1;
			
			
			biom_now = bioms[get_biom(chunktype2vec3i(cchunktype(cx,cz,x,y,z),chunkUp.x,chunkUp.y))];
			
			hightmap = get_terrain(
			chunktype2vec3i(cchunktype(cx,cz,x,y,z),chunkUp.x,chunkUp.y),
			biom_now.size,biom_now.times,biom_now.powfactor)+biom_now.height;
			
			vec3i test = chunktype2vec3i(cchunktype(cx,cz,x,y,z),chunkUp.x,chunkUp.y);
			
			int testx = ((int)(cx-chunkUp.x))*chunkx+x;
			int testz = ((int)(cz-chunkUp.y))*chunkz+z;
			
			
			y = hightmap;
			
			
				for(y=0;y<hightmap;y++){
					mychunk[cx][cz][x+1][y+1][z+1] = biom_now.blockdown;
				}
				
				if(hightmap < WaterLevel-5 && biom_now.lake){
					//lake
					mychunk[cx][cz][x+1][hightmap+1][z+1] = 9;
					
					for(i=WaterLevel;i>hightmap+1;i--){
						mychunk[cx][cz][x+1][i][z+1] = 7;
					}
					
					if(biom_now.ice){mychunk[cx][cz][x+1][WaterLevel][z+1] = 10;}
				}else{
					//normal tarrain
					mychunk[cx][cz][x+1][y+1][z+1] = biom_now.blockmiddle;
					mychunk[cx][cz][x+1][y+2][z+1] = biom_now.blockmiddle;
					mychunk[cx][cz][x+1][y+3][z+1] = biom_now.blockmiddle;
					mychunk[cx][cz][x+1][y+4][z+1] = biom_now.blockmiddle;
					mychunk[cx][cz][x+1][y+5][z+1] = biom_now.blockup;
					if(biom_now.snow){
						mychunk[cx][cz][x+1][y+6][z+1] = 11;
						LightHightMax[cx][cz] = MAX((int)LightHightMax[cx][cz],(int)y+7);
					}else{
						LightHightMax[cx][cz] = MAX((int)LightHightMax[cx][cz],(int)y+6);
					}
					//noise2 trees, lightcalculation trees
					if(noise2(abs(((int)(cx-chunkUp.x))*chunkx+x),abs(((int)(cz-chunkUp.y))*chunkz+z))==1){
						LightHightMax[cx][cz] = MAX((int)LightHightMax[cx][cz],(int)y+10);
						
						trees[treecount] = cvec4i(biom_now.tree,x,y+6,z);
						treecount += 1;
					}
				}
		}
	}
	
	//generrate trees
	//printf("treecount:%d\n",treecount);
	
	for(i=0;i<treecount;i++){
		tree_model(cx,cz,trees[i].x,trees[i].y,trees[i].z,trees[i].w);
	}
	

}


void setup_chunks(){
	int cx,cz,i,x,y,z=0;
	int a1 = (int)(chunkOld.x - chunkUp.x);
	int a2 = (int)(chunkOld.y - chunkUp.y);
	vec2i chunkMove = {
		chunkUp.x-chunkOld.x,
		chunkUp.y-chunkOld.y
	};
	
	for(cx=0;cx<chunkcount;cx++){
		for(cz=0;cz<chunkcount;cz++){
			//setup_chunk(cx,cz);
			if(1){
				if(!FirstFrame){save_chunk(cx,cz,-chunkOld.x+cx,-chunkOld.y+cz);}
				//printf("%d %d %d %d\n",cx,cz,chunkUp.x+cx,chunkUp.y+cz);
				//setup_chunk(cx,cz);
			}
			if(1){
				if(!load_chunk(cx,cz,-chunkUp.x+cx,-chunkUp.y+cz)){
					setup_chunk(cx,cz);
				}
			}
		}
	}

	for(cx=0;cx<chunkcount;cx++){
		for(y=0;y<chunky;y++){
			for(z=0;z<chunkz;z++){
				for(i=0;i<chunkcount-1;i++){
					mychunk[i+1	][cx	][0			][y+1][z+1		] = mychunk[i	][cx	][chunkx	][y+1][z+1		];
					mychunk[i	][cx	][chunkx+1	][y+1][z+1		] = mychunk[i+1][cx	][1		][y+1][z+1		];
					mychunk[cx	][i+1	][z+1			][y+1][0			] = mychunk[cx	][i	][z+1		][y+1][chunkx	];
					mychunk[cx	][i	][z+1			][y+1][chunkx+1] = mychunk[cx	][i+1	][z+1		][y+1][1			];
					
				}
				
			}
		}
	}
	FirstFrame = false;
}

vec3i GetLightLevel(int cx,int cz,int x,int y,int z){
	bool stop = 0;
	for(int i = y+1;i<LightHightMax[cx][cz];i++){
		if(mychunk[cx][cz] [x][i][z] && mychunk[cx][cz] [x][i][z] != 7){
			stop=1;break;}
	}
	if(stop)	{return cvec3i(8 ,8 ,8 );}
	else		{return cvec3i(16,16,16);}
}
void SetupChunkMesh(vec3f chunkpos,vec2i pos){ //chunkpos player = playerpos pos = chunknumber (array pos)
	vec3i LightLevel = {16,16,16};
	boolcube pages;
	for(int x = 0;x<chunkx;x++){
		for(int y=0;y<chunky;y++){
			for(int z=0;z<chunkz;z++){
				if(blockarray[mychunk[pos.x][pos.y][x+1][y+1][z+1]].height){
					pages = cboolcube(
						(bool)!mychunk[pos.x][pos.y][x+1][y+1]	[z+2],
						(bool)!mychunk[pos.x][pos.y][x+2][y+1]	[z+1],
								mychunk[pos.x][pos.y][x+1][y+2]	[z+1] != mychunk[pos.x][pos.y][x+1]	[y+1]	[z+1],//if non 16 pixel hight block reder up except of same block
						(bool)!mychunk[pos.x][pos.y][x+1][y+1]	[z],
						(bool)!mychunk[pos.x][pos.y][x]	[y+1]	[z+1],
						(bool)!mychunk[pos.x][pos.y][x+1][y]	[z+1]
					);
				}else{
						pages = cboolcube(
							((bool)!mychunk[pos.x][pos.y][x+1]	[y+1]	[z+2]	
								||blockarray[mychunk[pos.x][pos.y][x+1]	[y+1]	[z+2]].height
								||blockarray[mychunk[pos.x][pos.y][x+1]	[y+1]	[z+2]].transparency)
								&&pos.y*chunkz+z+1!=chunkz*chunkcount
								,
							((bool)!mychunk[pos.x][pos.y][x+2]	[y+1]	[z+1]	
								||blockarray[mychunk[pos.x][pos.y][x+2]	[y+1]	[z+1]].height
								||blockarray[mychunk[pos.x][pos.y][x+2]	[y+1]	[z+1]].transparency)
								&&pos.x*chunkx+x+1!=chunkx*chunkcount
								,
							((bool)!mychunk[pos.x][pos.y][x+1]	[y+2]	[z+1]	
								||blockarray[mychunk[pos.x][pos.y][x+1]	[y+2]	[z+1]].height
								||blockarray[mychunk[pos.x][pos.y][x+1]	[y+2]	[z+1]].transparency)
								,
							((bool)!mychunk[pos.x][pos.y][x+1]	[y+1]	[z]	
								||blockarray[mychunk[pos.x][pos.y][x+1]	[y+1]	[z]].height
								||blockarray[mychunk[pos.x][pos.y][x+1]	[y+1]	[z]].transparency)
								&&pos.y*chunkz+z!=0
								,
							((bool)!mychunk[pos.x][pos.y][x]	[y+1]	[z+1]		
								||blockarray[mychunk[pos.x][pos.y][x]		[y+1]	[z+1]].height
								||blockarray[mychunk[pos.x][pos.y][x]		[y+1]	[z+1]].transparency)
								&&pos.x*chunkx+x!=0
								,
							((bool)!mychunk[pos.x][pos.y][x+1]	[y]	[z+1]	
								||blockarray[mychunk[pos.x][pos.y][x+1]	[y]	[z+1]].height
								||blockarray[mychunk[pos.x][pos.y][x+1]	[y]	[z+1]].transparency)
						);
					}
						
				if((pages.p1||pages.p2||pages.p3||pages.p4||pages.p5||pages.p6)){//&&mychunk[pos.x][pos.y][x+1][y+1][z+1] != 0){
					if(EnableLight){
						LightLevel = GetLightLevel(pos.x,pos.y,x+1,y+1,z+1);
					}
					
					
					AddCubeMesh(blockarray[mychunk[pos.x][pos.y][x+1][y+1][z+1]],
						cvec3f(x+chunkpos.x*chunkx,y+chunkpos.y*chunky,z+chunkpos.z*chunkz),
						pages
						,LightLevel,(mychunk[pos.x][pos.y][x+1][y+1][z+1]==7&&
						mychunk[pos.x][pos.y][x+1][y+1][z+1]==mychunk[pos.x][pos.y][x+1][y+2][z+1]));
				}
			}
		}
	}
}

void SetupMesh(){
	int x = chunkcountmin;//-(chunkcount/2);
	int y = chunkcountmin;//-(chunkcount/2);
	for(int i = 0;i<MeshC;i++){
		vertices[i] = 0;
		texcoords[i] = 0;
		colors[i] = 0;
	}
	MeshC = 0;
	TexC = 0;
	ColC = 0;
	for(x=chunkcountmin;x<chunkcountmax;x++){
		for(y = chunkcountmin;y<chunkcountmax;y++){
				SetupChunkMesh(	cvec3f(x-chunkUp.x,0,y-chunkUp.y),
								cvec2i(x-chunkcountmin,y-chunkcountmin));
		}
	}
	//printf("4\n");
	
}

void chunk_update(){
	chunkUp.x = (int)player.x/chunkx; //chunk cord to int
	chunkUp.y = (int)player.z/chunkz;
	
	if((float)player.x > 0){chunkUp.x+=1;}
	if((float)player.z > 0){chunkUp.z+=1;}
	if(chunkOld.x != chunkUp.x||chunkOld.y != chunkUp.y){
		setup_chunks();
		SetupMesh();
		chunkOld.x = chunkUp.x;
		chunkOld.y = chunkUp.y;

	}
}
