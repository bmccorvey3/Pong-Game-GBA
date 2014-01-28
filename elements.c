//Brent McCorvey

#include "mylib.h"
#include "elements.h"
#include "text.h"
#include <stdio.h>

//not right yet				//FIX SCORE INCREMENTING AND GREEN BLOCK DETACHING WHEN HIT THE TOP

int row = 50;
int col = 120;
int oldrow = 50;
int oldcol = 120;
int rd = 1;
int cd = 1;
int size = 5;
int pNew = 80;
int cNew = 80;
static char lives_string[40];

void spawn_paddles() {
	p.r = 80;
	p.c = 0;
	p.width = 3;
	p.height = 8;
	comp.r = 80;
	comp.c = 237;
	comp.width = 3;
	comp.height = 8;
}

void spawn_lives() {
	p.lives = 3;
	p.score = 0;
}

void spawn_player() {
	drawRect(pNew,p.c,p.width,p.height,GREEN);
	drawRect(cNew,comp.c,comp.width,comp.height,GREEN);
}

void spawn_default() {
	drawRect(p.r,p.c,p.width,p.height,GREEN);
	drawRect(comp.r,comp.c,comp.width,comp.height,GREEN);
}

void move_player() {
	if (KEY_DOWN_NOW(BUTTON_UP)) {
		pNew = p.r;
		pNew = p.r - 5;
		drawRect(p.r+size,p.c,p.width,p.height,BLACK);
		drawRect(pNew,p.c,p.width,p.height,GREEN);
		p.r = pNew;
		if (p.r < 20) {
			p.r = 20;
		}
	}
	else if (KEY_DOWN_NOW(BUTTON_DOWN)) {
		pNew = p.r;
		pNew = p.r + 5;
		drawRect(p.r-size,p.c,p.width,p.height,BLACK);
		drawRect(pNew,p.c,p.width,p.height,GREEN);
		p.r = pNew;
		if (p.r > HEIGHT- p.height + 1) {
			p.r = HEIGHT - p.height -size;
		}
	}
}

void move_computer() {
	if(row < comp.r &&(col>180)) {
		cNew = comp.r;
		cNew = comp.r - 5;
		drawRect(comp.r,comp.c,comp.width,comp.height,BLACK);
		drawRect(cNew,comp.c,comp.width,comp.height,GREEN);
		comp.r = cNew;
		if (comp.r < 0) {
			comp.r = 0;
		}
	}
	else if(row > (comp.r + comp.height) && (col>180)) {
		cNew = comp.r;
		cNew = comp.r + 5;
		drawRect(comp.r-size,comp.c,comp.width,comp.height,BLACK);
		drawRect(cNew,comp.c,comp.width,comp.height,GREEN);
		comp.r = cNew;
		if (comp.r > HEIGHT - comp.height + 1) {
			comp.r = HEIGHT - comp.height + 1;
		}
	}
}

void reset_ball() {
	row = 50;
	col = 120;
	oldrow = 50;
	oldcol = 120;
	rd = 1;
	cd = 1;
	size = 5;
}

void move_ball() {

	row +=rd;
	col+=cd;

	if(row<0) {
		row = 0;
		rd = -rd;
	}

	if(row<20) {
		rd = -rd;
	}

	if (row>159-size+1) {
		row = 159-size+1;
		rd = -rd;
	}
	if(col<0) {
		col = 0;
		cd = -cd;
		p.lives = p.lives--;
		blackScreen(WIDTH,HEIGHT);
		spawn_player();
		reset_ball();
		lives_text();
	}
	if(col>239-size+1) {
		col = 239-size+1;
		cd = -cd;
		blackScreen(WIDTH,HEIGHT);		//FIX WHEN DONE
		spawn_player();
		reset_ball();
		lives_text();
	}   
	waitForVblank();
    drawRect(oldrow, oldcol, size, size, BLACK);
    drawRect(row, col, size, size, WHITE);
    oldrow = row;
    oldcol = col; 
}

void check_player_collision() {
	if(col<p.width+2 && (((pNew+p.height-row+size+1) > 0) && ((pNew-row-size-1)<= 0))){
		cd = -cd;
	}
}

void check_computer_collision() {
	if((col>239-comp.width-size-3) && (((cNew+comp.height-row+size+1) > 0) && ((cNew-row-size-1)<= 0))) {
		cd = -cd;
		p.score = p.score++;
		blackScreen(WIDTH,HEIGHT);
		spawn_player();					//FIX!!! COLLISION AND SCORE INCREMENT!!!	
		lives_text();
	}
}

void lives_text() {
	sprintf(lives_string,"Lives: %d", p.lives);
	drawString(5,5,lives_string,RED);
	sprintf(lives_string,"Score: %d", p.score);
	drawString(5,185,lives_string,RED);
}