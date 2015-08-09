#include <GL/glut.h>//Drawing funciton
#include<cstdio>
#include<string>
#include<stdlib.h>
#include<cstring>
using namespace std;

/*
 * c++ file containing chess driver
 *
 * Copyright 2014 Vedsar
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

struct ntt {
	char name[3];
	int from[2];
	int to[2];
};
void draw_sq(float x1,float y1,int r,int g,int b);
void draw_square();
void draw_board();
void chg_flag(int *flag);
void draw_pieces(char mat[8][8][3]);
void get_points(int x,int y,float *x1,float *y1);
void init_mat(char mat[8][8][3]);
void draw_rock(int c,int x,int y);
void draw_queen(int c,int x,int y);
void draw_king(int c,int x,int y);
void draw_knight(int c,int x,int y);
void draw_bishop(int c,int x,int y);
void draw_pawn(char c,int x,int y);
void map(int x,int y,float *x1,float *y1);
void reverse_map(float x,float y,int *x1,int *y1);
void prnt(char mat[8][8][3]);
int validate_move(int oldx,int oldy,int newx,int newy,char piece,char color,int move,char str[100]);
int rock_move_check(int oldx,int oldy,int newx,int newy);
int bishop_move_check(int oldx,int oldy,int newx,int newy);
int knight_move_check(int oldx,int oldy,int newx,int newy);
int king_move_check(int oldx,int oldy,int newx,int newy);
int queen_move_check(int oldx,int oldy,int newx,int newy);
int pawn_move_check(int oldx,int oldy,int newx,int newy,char color);
int abs(int x);
void change_turn(int *mve);
/*second window function*/
void notation(float r, float g, float b, struct ntt nttion[10],int len);
/*third window function*/
void err_print(char *all_error);
