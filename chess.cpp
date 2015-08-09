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

//game matrix
char mat[8][8][3];
//mouse pointer initial and end position
int sx,sy,ex,ey,flag;

//notation structure
struct ntt nttion[10];
//error string
char all_error[100];
int len=0;
int move=0,p_move=0,move_flag=0;
char ch[3];
void init() {
	int i,j,k;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(000,000);
	glutInitWindowSize(500,500);
	glutCreateWindow("Chess");
	init_mat(mat);
	flag=0;
}
void draw(void) {
	//Background color
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT );
	//draw lines
	draw_board();
	//Draw black and white squares
	draw_square();
	//draw_pieces
	draw_pieces(mat);
	glFlush();
}
void move_piece(int b,int s,int x,int y) {
	float x1,y1,r,g,b1;
	int matx,maty,i,j,k;
	string piece;
	if((b==GLUT_LEFT_BUTTON)&&(s==GLUT_DOWN)&&flag==0) {
		sx=x;
		sy=y;
		flag=1;
	}
	else if((b==GLUT_RIGHT_BUTTON)&&(s==GLUT_DOWN)&&flag==1) {
		ex=x;
		ey=y;
		flag=0;
		//get the old matrix indeces
		get_points(sx,sy,&x1,&y1);
		reverse_map(y1,x1,&matx,&maty);
		i=matx;j=maty;
		//get the new matrix indeces
		get_points(ex,ey,&x1,&y1);
		reverse_map(y1,x1,&matx,&maty);
		//validate the move
		if(validate_move(i,j,matx,maty,mat[i][j][1],mat[i][j][0],move,all_error)) {
		//notations
			if(len==10) {
				//shift the piece
				for(k=0;k<10;k++) {
					nttion[k].from[0]=nttion[k+1].from[0];
					nttion[k].from[1]=nttion[k+1].from[1];
					
					nttion[k].to[0]=nttion[k+1].to[0];
					nttion[k].to[1]=nttion[k+1].to[1];
					
					nttion[k].name[0]=nttion[k+1].name[0];
					nttion[k].name[1]=nttion[k+1].name[1];
					nttion[k].name[2]=nttion[k+1].name[2];
				}
				nttion[len-1].from[0]=i;
				nttion[len-1].from[1]=j;
				
				nttion[len-1].to[0]=matx;
				nttion[len-1].to[1]=maty;
				
				nttion[len-1].name[0]=mat[matx][maty][0];
				nttion[len-1].name[1]=mat[matx][maty][1];
				nttion[len-1].name[2]=mat[matx][maty][2];
			}
			else {
				nttion[len].from[0]=i;
				nttion[len].from[1]=j;
				
				nttion[len].to[0]=matx;
				nttion[len].to[1]=maty;
				
				nttion[len].name[0]=mat[i][j][0];
				nttion[len].name[1]=mat[i][j][1];
				nttion[len].name[2]=mat[i][j][2];
				len++;
			}
			change_turn(&move);
		//copy the piece to new position
			mat[matx][maty][0]=mat[i][j][0];
			mat[matx][maty][1]=mat[i][j][1];
			mat[matx][maty][2]=mat[i][j][2];
			//delete the old piece position
			mat[i][j][0]='e';mat[i][j][1]='e';mat[i][j][2]='e';
		}
	}
	glutPostRedisplay();
}
void write(void) {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	notation(1,1,1,nttion,len);
	glutPostRedisplay();
}
void err(void) {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	err_print(all_error);
	glutPostRedisplay();
}
//Main program
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	//Simple buffer
	init();
	glutDisplayFunc(draw);
	glutMouseFunc(move_piece);
	//second window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(500,000);
	glutInitWindowSize(200,500);
	glutCreateWindow("Notations");
	glutDisplayFunc(write);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(700,000);
	glutInitWindowSize(300,100);
	glutCreateWindow("Error");
	glutDisplayFunc(err);
	glutMouseFunc(move_piece);
	glutMainLoop();
	return 0;
}
