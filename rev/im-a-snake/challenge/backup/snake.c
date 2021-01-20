#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>

#define TIMEOUT 1000

void init();
void kill();
void layout();
void play();
int head_not_border();
int head_not_body();
int eat();
int not_secret_door();
void layout2();

// global variables:
int maxx, maxy, centrex, centrey, status, bodyLen;
int bodyx[1000], bodyy[1000];
int foodx, foody;
int secretx, secrety;
char *dir;
char *over = "GAME OVER";
char *exit_msg = "Press F1 to exit";
int ch;

int main(){
	init();

	layout();
	play();
	getch();
	kill();

	return 0;
}

void init(){
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	cbreak();
	timeout(TIMEOUT);
	curs_set(0);

	getmaxyx(stdscr, maxy, maxx);
	centrex = maxx / 2;
	centrey = maxy / 2;

	srand(time(0));
	foodx = (rand() % (maxx - 5)) + 2;
	foody = (rand() % (maxy - 5)) + 2;

	status = 1;
	bodyLen = 5;

	for(int i = 0; i<bodyLen; i++){
		bodyx[i] = centrex - i;
		bodyy[i] = centrey;
	}	

	dir = "right";

	if(maxx > maxy){
		secretx = maxy;
		secrety = 1;
	} else {
		secrety = maxx;
		secretx = 1;
	}
}

void layout(){
	mvprintw(1,maxx-2, "+");
	mvprintw(1,1,"+");
	mvprintw(maxy-2, maxx-2, "+");
	mvprintw(maxy-2,1,"+");

	for(int i = 2;i<maxx-2; i++){
		mvprintw(1, i, "-");
		mvprintw(maxy-2, i, "-");
	}

	for(int i = 2; i<maxy-2; i++){
		mvprintw(i, 1, "|");
		mvprintw(i, maxx-2, "|");
	}

	attron(A_BLINK | A_BOLD);
	mvprintw(foody, foodx, "o");
	attroff(A_BLINK | A_BOLD);

	mvprintw(0, maxx-10, "%d x %d", maxy, maxx);

	mvprintw(maxy-1, (maxx - strlen(exit_msg)), exit_msg);

	refresh();
}

void play(){

	while(status){
		attron(A_BLINK | A_BOLD);
		mvprintw(foody, foodx, "o");
		attroff(A_BLINK | A_BOLD);
	
		for(int i = 0; i<bodyLen; i++){
			mvprintw(bodyy[i], bodyx[i], "#");
		}
		
		mvprintw(maxy-1, 0, "%d %d   ", bodyy[0], bodyx[0]);
	
		ch = getch();
		switch(ch){
			case KEY_F(2):	status = 0;
											break;
			case KEY_RIGHT:	mvprintw(0,0,"RIGHT");
											dir = "right";
											break;
			case KEY_LEFT:	mvprintw(0,0,"LEFT ");
											dir = "left";
											break;
			case KEY_UP:		mvprintw(0,0,"UP   ");
											dir = "up";
											break;
			case KEY_DOWN:	mvprintw(0,0,"DOWN ");
											dir = "down";
											break;		
		}

		if(strcmp(dir, "right") == 0 && head_not_border() && head_not_body() && eat() && not_secret_door()){
			mvprintw(bodyy[bodyLen-1],bodyx[bodyLen-1]," ");
			for(int i = bodyLen; i>0; i--){
				bodyx[i] = bodyx[i-1];
				bodyy[i] = bodyy[i-1];
			}
			bodyx[0] = bodyx[1] + 1;
			bodyy[0] = bodyy[1];
		}	
		else if(strcmp(dir, "left") == 0 && head_not_border() && head_not_body() && eat() && not_secret_door()){
			mvprintw(bodyy[bodyLen-1],bodyx[bodyLen-1]," ");
			for(int i = bodyLen; i>0; i--){
				bodyx[i] = bodyx[i-1];
				bodyy[i] = bodyy[i-1];
			}
			bodyx[0] = bodyx[1] - 1;
			bodyy[0] = bodyy[1];
		}
		else if(strcmp(dir, "down") == 0 && head_not_border() && head_not_body() && eat() && not_secret_door()){
			mvprintw(bodyy[bodyLen-1],bodyx[bodyLen-1]," ");
			for(int i = bodyLen; i>0; i--){
				bodyx[i] = bodyx[i-1];
				bodyy[i] = bodyy[i-1];
			}
			bodyx[0] = bodyx[1];
			bodyy[0] = bodyy[1] + 1;
		}
		else if(strcmp(dir, "up") == 0 && head_not_border() && head_not_body() && eat() && not_secret_door()){
			mvprintw(bodyy[bodyLen-1],bodyx[bodyLen-1]," ");
			for(int i = bodyLen; i>0; i--){
				bodyx[i] = bodyx[i-1];
				bodyy[i] = bodyy[i-1];
			}
			bodyx[0] = bodyx[1];
			bodyy[0] = bodyy[1] - 1;
		}
	}
	refresh();
}

void kill(){
	endwin();
	curs_set(1);
	timeout(-1);
}

int head_not_border(){
	if(not_secret_door() == 0){
		return 1;
	}

	if((strcmp(dir, "right") == 0) && (bodyx[0] == maxx-3)){
		mvprintw(centrey, (centrex - (strlen(over) / 2)), over);
		timeout(-1);
		status = 0; 
		return 0;
	}
	if((strcmp(dir, "left") == 0) && (bodyx[0] == 2)){
		mvprintw(centrey, (centrex - (strlen(over) / 2)), over);
		timeout(-1);
		status = 0; 
		return 0;
	}
	if((strcmp(dir, "up") == 0) && (bodyy[0] == 2)){
		mvprintw(centrey, (centrex - (strlen(over) / 2)), over);
		timeout(-1);
		status = 0; 
		return 0;
	}
	if((strcmp(dir, "down") == 0) && (bodyy[0] == maxy-3)){
		mvprintw(centrey, (centrex - (strlen(over) / 2)), over);
		timeout(-1);
		status = 0; 
		return 0;
	}

	return 1;
}

int head_not_body(){
	int x,y;
	
	if(strcmp(dir, "right") == 0){
		x = bodyx[0] + 1;
		y = bodyy[0];
	} else if(strcmp(dir, "left") == 0){
		x = bodyx[0] - 1;
		y = bodyy[0];
	} else if(strcmp(dir, "up") == 0){
		x = bodyx[0];
		y = bodyy[0] - 1;
	} else if(strcmp(dir, "down") == 0){
		x = bodyx[0];
		y = bodyy[0] + 1;
	}

	for(int i = 1; i<bodyLen; i++){
		if(x == bodyx[i] && y == bodyy[i]) {
			mvprintw(centrey, (centrex - (strlen(over) / 2)), over);
			timeout(-1);
			status = 0;
			return 0;
		}
	}	

	return 1;
}

int eat(){
	int x,y;

	if(strcmp(dir, "right") == 0){
		x = bodyx[0] + 1;
		y = bodyy[0];
	} else if(strcmp(dir, "left") == 0){
		x = bodyx[0] - 1;
		y = bodyy[0];
	} else if(strcmp(dir, "up") == 0){
		x = bodyx[0];
		y = bodyy[0] - 1;
	} else if(strcmp(dir, "down") == 0){
		x = bodyx[0];
		y = bodyy[0] + 1;
	}


	if(x == foodx && y == foody){
		bodyLen += 1;
		mvprintw(foody, foodx," ");

		foodx = (rand() % (maxx - 5)) + 2;
		foody = (rand() % (maxy - 5)) + 2;
		
		attron(A_BLINK | A_BOLD);
		mvprintw(foody, foodx, "0");
		attroff(A_BLINK | A_BOLD);

		return 0;
	}
	return 1;
}

int not_secret_door(){
	int x,y;

	if(strcmp(dir, "right") == 0){
		x = bodyx[0] + 1;
		y = bodyy[0];
	} else if(strcmp(dir, "left") == 0){
		x = bodyx[0] - 1;
		y = bodyy[0];
	} else if(strcmp(dir, "up") == 0){
		x = bodyx[0];
		y = bodyy[0] - 1;
	} else if(strcmp(dir, "down") == 0){
		x = bodyx[0];
		y = bodyy[0] + 1;
	}
	
	if(x == secretx && y == secrety){
		layout2();
	}
}

void layout2(){
	char *flag = "testFlag{HelloWprld}";

	mvprintw(centrey, (centrex - (strlen(flag) / 2)), flag);
}
