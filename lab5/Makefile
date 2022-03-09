CC=gcc
includes:= -Ilib/game/include -Ihosted/include -Ilib/API/include
DEPS = lib/game/rules.h,lib/game/game.h,hosted/include/serial.h
hosted: hosted/src/hosted.c 
	gcc $(includes) hosted/src/serial.c hosted/src/hosted.c -o hosted.o