#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

extern SDL_Window* gWindow ;
extern SDL_Renderer* gRenderer ;
extern TTF_Font *gFont;

extern Mix_Chunk *explore;
extern Mix_Chunk *sphere;
extern Mix_Chunk *laser;

const int time_play = 100;
const int NUM_PlayPower = 4;
const int GFOO_WIDTH = 77;
const int GFOO_HEIGHT = 52;
const int GFOO_VEL = 10;
const int Explore_Width = 165;
const int Explore_Height = 165;
const int Threat_WIDTH = 80;
const int Threat_HEIGHT = 33;
const int WIDTH_BACKGROUND = 4800;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int NUM_THREATS = 3;
const int NUM_FRAME = 4;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const int start_Ox = 100;
const int start_Oy = 500;
const int itemMenu = 2;
const int itemGame_over = 2;
const int width_frame_ = 256;
const int height_frame_ = 256;
const int FRAME_NUM_32 = 32;
const int width_boss = 350;
const int height_boss = 155;

const int WIDTH_LASER = 40;
const int HEIGHT_LASER = 5;
const int WIDTH_SPHERE = 10;
const int HEIGHT_SPHERE = 10;
const int WIDTH_THREAT = 80;
const int HEIGHT_THREAT = 33;

#endif