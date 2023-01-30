//image stuff
#define tarrainImageSize 256
#define blockSize 16

//texuture stuff
#define terrain_width 16
#define terrain_Height 16
#define TransperentTextures 1

//chunk size
#define chunkx 16
#define chunky 256
#define chunkz 16

//chunk count
#define chunkcount 5
#define chunkcountmin -((int)(chunkcount/2))
#define chunkcountmax ((int)(chunkcount/2))+1

//bioms
#define biomscount 4
#define biom_size 40

//mesh
#define ZCubeBuffer 1

//lighting
#define LightLevelSize 16
#define EnableLight 1

//terrain gen
#define WaterLevel 47

//paths
#define IMAGE_PATH "bin/images/terrain.png"
#define CHUNK_PATH "bin/files/chunks/chunk%dx%d"
