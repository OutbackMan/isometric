#!/bin/bash

gcc common.c isometric.c events.c update.c draw.c main.c -o isometric -lSDL2 -lSDL2_image 
