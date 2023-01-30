# MinecraftClone

A minecraft clone from scratch written in c using OpenGL glut and libpng.

## run(only Linux):
1. cd to bin
2. run ./bin/out

## compile(only Linux)
make sure you installed opengl and libpng:
	- /usr/include/GL
	- /usr/include/png.h


1. cd to bin
2. remove bin/out
3. use gcc src/main.c -o bin/out -DPNG_IMAGE_TES -g -lpng -lm -I /usr/include -lGL -lglut -lGLU
4. run ./bin/out


## TODO:
- fix block selection

- (colision)

- (better lighting)

- (inventor & GUI)

- (Day Night)

- (more bioms & blocks)

