
all: sdl_test

sdl_test: sdl_test.c
	gcc -o sdl_test sdl_test.c -lSDL2
