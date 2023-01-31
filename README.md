# MinecraftClone

A minecraft clone from scratch written in c using OpenGL glut and libpng.

![screenshot1](https://github.com/Ztirom45/MinecraftClone/blob/main/screenshots/shot1.png)
![screenshot2](https://github.com/Ztirom45/MinecraftClone/blob/main/screenshots/shot2.png)
![screenshot3](https://github.com/Ztirom45/MinecraftClone/blob/main/screenshots/shot3.png)
![screenshot4](https://github.com/Ztirom45/MinecraftClone/blob/main/screenshots/shot4.png)
![screenshot5](https://github.com/Ztirom45/MinecraftClone/blob/main/screenshots/shot5.png)
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

