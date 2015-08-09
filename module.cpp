#include"module.h"
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

void chg_flag(int *flag) {
	if(*flag==0)
		*flag=1;
	else
		*flag=0;
}
void draw_sq(float x1,float y1,int r,int g,int b) {
	glColor3f(r,g,b);
	glBegin(GL_QUADS);
		glVertex2f(x1,y1);
		glVertex2f(x1+0.25,y1);
		glVertex2f(x1+0.25,y1+0.25);
		glVertex2f(x1,y1+0.25);
	glEnd();
}
void draw_square() {
	float i=0,j=0;
	int flag=1;
	for(i=-1;i<1;i+=.25) {
		chg_flag(&flag);
		for(j=-1;j<1;j+=.25) {
			if(flag==0)
				draw_sq(i,j,0,0,0);
			else
				draw_sq(i,j,1,1,1);
			chg_flag(&flag);
		}
	}
}
void draw_board() {
	float i=-.8;
	glColor3d(1,1,1);
	glLineWidth(5);
	for(i=-.75;i<1;i+=.25) {
		glBegin(GL_LINES);
			//vertical lines
			glVertex2f(i,1);
			glVertex2f(i,-1);
			//horizontal lines
			glVertex2f(-1,i);
			glVertex2f(1,i);
		glEnd();
	}
}
void init_mat(char mat[8][8][3]) {
	int i,j,k;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			for(k=0;k<3;k++)
			mat[i][j][k]='e';
	//white pieces
	for(i=0;i<8;i++) {
		mat[0][i][0]='w';
		mat[0][i][2]='1';
	}
	mat[0][0][1]='r';
	mat[0][1][1]='n';
	mat[0][2][1]='b';
	mat[0][3][1]='k';
	mat[0][4][1]='q';
	mat[0][5][1]='b';mat[0][5][2]='2';
	mat[0][6][1]='n';mat[0][6][2]='2';
	mat[0][7][1]='r';mat[0][7][2]='2';
	for(i=0;i<8;i++) {
		mat[1][i][0]='w';
		mat[1][i][1]='p';
	}
	mat[1][0][2]='1';
	mat[1][1][2]='2';
	mat[1][2][2]='3';
	mat[1][3][2]='4';
	mat[1][4][2]='5';
	mat[1][5][2]='6';
	mat[1][6][2]='7';
	mat[1][7][2]='8';
	//black pieces
	for(i=0;i<8;i++) {
		mat[7][i][0]='b';
		mat[7][i][2]='1';
	}
	mat[7][0][1]='r';
	mat[7][1][1]='n';
	mat[7][2][1]='b';
	mat[7][3][1]='k';
	mat[7][4][1]='q';
	mat[7][5][1]='b';mat[7][5][2]='2';
	mat[7][6][1]='n';mat[7][6][2]='2';
	mat[7][7][1]='r';mat[7][7][2]='2';
	for(i=0;i<8;i++) {
		mat[6][i][0]='b';
		mat[6][i][1]='p';
	}
	mat[6][0][2]='1';
	mat[6][1][2]='2';
	mat[6][2][2]='3';
	mat[6][3][2]='4';
	mat[6][4][2]='5';
	mat[6][5][2]='6';
	mat[6][6][2]='7';
	mat[6][7][2]='8';
}
void draw_pieces(char mat[8][8][3]) {
	int i,j;
	for(i=0;i<8;i++) {
		for(j=0;j<8;j++) {
			if(mat[i][j][0]!='e') {
				//get the unique piece and call its function to draw with location and color
				//location and color will be obtained from matrix value
				if(mat[i][j][1]=='p') {
					draw_pawn(mat[i][j][0],j,i);
				}
				else if(mat[i][j][1]=='r') {
					draw_rock(mat[i][j][0],j,i);
				}
				else if(mat[i][j][1]=='b') {
					draw_bishop(mat[i][j][0],j,i);
				}
				else if(mat[i][j][1]=='n') {
					draw_knight(mat[i][j][0],j,i);
				}
				else if(mat[i][j][1]=='k') {
					draw_king(mat[i][j][0],j,i);
				}
				else if(mat[i][j][1]=='q') {
					draw_queen(mat[i][j][0],j,i);
				}
			}
		}
	}
}
void get_points(int x,int y,float *x1,float *y1) {
	*x1=(float)x/glutGet(GLUT_WINDOW_WIDTH);
	*y1=(float)y/glutGet(GLUT_WINDOW_HEIGHT);
}
void draw_rock(int c,int x,int y) {
	float x1,y1;
	get_points(x,y,&x1,&y1);
	map(x,y,&x1,&y1);
	x1=x1+.050;
	y1=y1-.025;
	if(c=='w')
		glColor3f(1,1,0);
	else
		glColor3f(0,1,1);
	glBegin(GL_QUADS);
		glVertex2f(x1,y1);
		glVertex2f(x1+0.15,y1);
		glVertex2f(x1+0.15,y1-0.2);
		glVertex2f(x1,y1-0.2);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(x1-0.05,y1);
		glVertex2f(x1+0.20,y1);
		glVertex2f(x1-0.05,y1-0.2);
		glVertex2f(x1+.20,y1-0.2);
	glEnd();
}
void draw_queen(int c,int x,int y) {
	float x1,y1;
	get_points(x,y,&x1,&y1);
	map(x,y,&x1,&y1);
	x1=x1+.050;
	y1=y1-.025;
	if(c=='w')
		glColor3f(1,1,0);
	else
		glColor3f(0,1,1);
	glBegin(GL_QUADS);
		glVertex2f(x1+0.03,y1-.07);
		glVertex2f(x1+0.12,y1-.07);
		glVertex2f(x1+0.15,y1-0.20);
		glVertex2f(x1,y1-0.20);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(x1+0.15,y1);
		glVertex2f(x1,y1);
		glVertex2f(x1+0.03,y1-.07);
		glVertex2f(x1+0.12,y1-.07);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(x1-0.05,y1-0.2);
		glVertex2f(x1+.20,y1-0.2);
	glEnd();
}
void draw_king(int c,int x,int y) {
	float x1,y1;
	get_points(x,y,&x1,&y1);
	map(x,y,&x1,&y1);
	x1=x1+.050;
	y1=y1-.025;
	if(c=='w')
		glColor3f(1,1,0);
	else
		glColor3f(0,1,1);
	glBegin(GL_QUADS);
		glVertex2f(x1,y1-.05);
		glVertex2f(x1+0.15,y1-.05);
		glVertex2f(x1+0.15,y1-0.2);
		glVertex2f(x1,y1-0.2);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(x1-0.05,y1-0.2);
		glVertex2f(x1+.20,y1-0.2);
		glVertex2f(x1-0.02,y1-0.1);
		glVertex2f(x1+.04,y1+.025);
		glVertex2f(x1+.1,y1+0.025);
		glVertex2f(x1+0.17,y1-0.095);
	glEnd();
}
void draw_knight(int c,int x,int y) {
	float x1,y1;
	get_points(x,y,&x1,&y1);
	map(x,y,&x1,&y1);
	x1=x1+.050;
	y1=y1-.025;
	if(c=='w')
		glColor3f(1,1,0);
	else
		glColor3f(0,1,1);
	glBegin(GL_QUADS);
		glVertex2f(x1+0.05,y1-.1);
		glVertex2f(x1+0.12,y1-.1);
		glVertex2f(x1+0.15,y1-0.20);
		glVertex2f(x1,y1-0.20);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(x1+0.13,y1+.020);
		glVertex2f(x1+0.12,y1-0.10);
		glVertex2f(x1+0.03,y1-0.03);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(x1-0.05,y1-0.2);
		glVertex2f(x1+.20,y1-0.2);
	glEnd();
}
void draw_bishop(int c,int x,int y) {
	float x1,y1;
	get_points(x,y,&x1,&y1);
	map(x,y,&x1,&y1);
	x1=x1+.050;
	y1=y1-.025;
	if(c=='w')
		glColor3f(1,1,0);
	else
		glColor3f(0,1,1);
	glBegin(GL_TRIANGLES);
		glVertex2f(x1+0.08,y1+.018);
		glVertex2f(x1+0.02,y1-0.2);
		glVertex2f(x1+0.14,y1-0.2);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(x1-0.05,y1-0.2);
		glVertex2f(x1+.20,y1-0.2);
	glEnd();
}
void draw_pawn(char c,int x,int y) {
	float x1,y1;
	map(x,y,&x1,&y1);
	x1=x1+.050;
	y1=y1-.025;
	if(c=='w')
		glColor3f(1,1,0);
	else
		glColor3f(0,1,1);
	glBegin(GL_TRIANGLES);
		glVertex2f(x1+0.08,y1-0.05);
		glVertex2f(x1+0.02,y1-0.2);
		glVertex2f(x1+0.14,y1-0.2);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(x1-0.05,y1-0.2);
		glVertex2f(x1+.20,y1-0.2);
	glEnd();
}
void map(int x,int y,float *x1,float *y1) {
	if(x==0)
		*x1=-1;
	if(x==1)
		*x1=-.75;
	if(x==2)
		*x1=-.5;
	if(x==3)
		*x1=-.25;
	else
		*x1=(x-4)*0.25;
	if(y==0)
		*y1=1;
	if(y==1)
		*y1=.75;
	if(y==2)
		*y1=.5;
	if(y==3)
		*y1=.25;
	else
		*y1=(y-4)*0.25*-1;
}
void reverse_map(float x,float y,int *x1,int *y1) {
	x=x*8;y=y*8;
	*x1=x;
	*y1=y;
}
void prnt(char mat[8][8][3]) {
	int i,j;
	for(i=0;i<8;i++) {
		for(j=0;j<8;j++) {
			printf("%c%c%c ",mat[i][j][0],mat[i][j][1],mat[i][j][2]);
		}
		printf("\n");
	}
}
void change_turn(int *mve) {
	if(*mve==0)
		*mve=1;
	else
		*mve=0;
}
int validate_move(int oldx,int oldy,int newx,int newy,char piece,char color,int move,char *str) {
	if((oldx==newx)&&(oldy==newy)) {
		strcpy(str,"Piece not moved");
		return 0;
	}
	else if((color=='w')&&(move==1)) {
		strcpy(str,"Its black's turn");
		return 0;
	}
	else if((color=='b')&&(move==0)) {
		strcpy(str,"Its white's turn");
		return 0;
	}
	else if(piece=='r') {
		if(rock_move_check(oldx,oldy,newx,newy)) {
			return 1;
		}
		else {
			strcpy(str,"Wrong Rock Move. Rock moves straight");
			return 0;
		}
	}
	else if(piece=='n') {
		if(knight_move_check(oldx,oldy,newx,newy))
			return 1;
		else {
			strcpy(str,"Wrong Knight Move. Knight moves L");
			return 0;
		}
	}
	else if(piece=='q') {
		if(queen_move_check(oldx,oldy,newx,newy))
			return 1;
		else {
			strcpy(str,"Wrong Quine Move. Quiue moves either straing or diagonal");
			return 0;
		}
	}
	else if(piece=='k') {
		if(king_move_check(oldx,oldy,newx,newy))
			return 1;
		else {
			strcpy(str,"Wrong King Move. King moves one step to surrounding");
			return 0;
		}
	}
	else if(piece=='p') {
		if(pawn_move_check(oldx,oldy,newx,newy,color))
			return 1;
		else {
			strcpy(str,"Wrong pawn Move. pawn moves one step straight");
			return 0;
		}
	}
	else if(piece=='b') {
		if(bishop_move_check(oldx,oldy,newx,newy))
			return 1;
		else {
			strcpy(str,"Wrong Bishop Move. Bishop moves diagonal");
			return 0;
		}
	}
	else {
		strcpy(str,"Unknown error happened");
		return 0;
	}
}
int rock_move_check(int oldx,int oldy,int newx,int newy) {
	return ((oldx==newx)||(oldy==newy));
}
int bishop_move_check(int oldx,int oldy,int newx,int newy) {
	return (abs(oldx-newx)==abs(oldy-newy));
}
int knight_move_check(int oldx,int oldy,int newx,int newy) {
	return (((abs(oldx-newx)==2)&&(abs(oldy-newy)==1))||((abs(oldx-newx)==1)&&(abs(oldy-newy)==2)));
}
int queen_move_check(int oldx,int oldy,int newx,int newy) {
	return ((rock_move_check(oldx,oldy,newx,newy))||(bishop_move_check(oldx,oldy,newx,newy)));	
}
int king_move_check(int oldx,int oldy,int newx,int newy) {
	return (((abs(oldx-newx)==1)&&(abs(oldy-newy)==1))||((abs(oldx-newx)==1)&&(abs(oldy-newy)==0))||((abs(oldx-newx)==0)&&(abs(oldy-newy)==1)));
}
int pawn_move_check(int oldx,int oldy,int newx,int newy,char c) {
	if(c=='b')
		return (((oldx-newx)==1)&&((oldy-newy)==0));
	else
		return (((newx-oldx)==1)&&((newy-oldy)==0));
}
int abs(int x) {
	if(x<0)
		return -x;
	else
		return x;
}
/****************************************************************************
SECOND WINDOW CODING IS HERE
****************************************************************************/
void notation(float r, float g, float b, struct ntt nttion[10],int len) {
  glColor3f( r, g, b );
  //printf("%s",string);
  int i,j,k,l;
  for(i=0;i<len;i++) {
  	glRasterPos2f(-0.9,1-(float)i/5-0.1);
  	//piece name
		for(k=0;k<3;k++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, nttion[i].name[k]);
		}
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
		for(k=0;k<2;k++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (char)(((int)'0')+(nttion[i].from[k])));
		}
  	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
  	for(k=0;k<2;k++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (char)(((int)'0')+nttion[i].to[k]));
  	}
  }
}
/****************************************************************************
THIRD WINDOW CODING IS HERE
****************************************************************************/
void err_print(char all_error[100]) {
	char ch;
	int i=0;
  glRasterPos2f(-0.9,0.8);
  while((ch=all_error[i++])!='\0') {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, ch);
  }
}
