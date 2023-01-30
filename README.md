# MinecraftClone

A minecraft clone from scratch written in c using OpenGL glut and libpng.

##run(only Linux):
cd to bin
run ./bin/out

##compile(only Linux)
make sure you installed opengl and libpng:

/usr/include/GL

/usr/include/png.h


cd to bin

remove bin/out

use gcc src/main.c -o bin/out -DPNG_IMAGE_TES -g -lpng -lm -I /usr/include -lGL -lglut -lGLU

run ./bin/out

## TODO:
fix block selection

(colision)

(better lighting)

(inventor & GUI)

(Day Night)

(more bioms & blocks)

