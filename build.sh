#!/bin/bash

gcc $(pkg-config --cflags sdl2) common.c isometric.c events.c update.c draw.c main.c -o isometric -pthread -lSDL2 -lSDL2_image 
