# MinecraftClone

A minecraft clone from scratch written in c using OpenGL glut and libpng.

## run(only Linux):

run ./bin/out

## compile(only Linux)
make sure you installed opengl and libpng:
	- /usr/include/GL
	- /usr/include/png.h


1. remove bin/out
2. use gcc src/main.c -o bin/out -DPNG_IMAGE_TES -g -lpng -lm -I /usr/include -lGL -lglut -lGLU
3. run ./bin/out


## TODO:
- fix block selection

- fix chunk update(remove changes)

- fix chunk update(remove changes)

- fix lighting height upadate while block placment

- (colision)

- (better lighting)

- (inventor & GUI)

- (Day Night)

- (more bioms & blocks)

