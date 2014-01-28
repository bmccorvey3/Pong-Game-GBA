//Brent McCorvey

#include "mylib.h"
#include "elements.h"
#include "start.h"
#include "game_over.h"
#include "win.h"
#include "text.h"
#include "yellowPong.h"
#include <string.h>
#include <stdio.h>

int main() {

	REG_DISPCTL = MODE3 | BG2_ENABLE;

	int begin = 0;

	while(1) {

		if (!begin) {
			drawImage3(0,0,START_WIDTH,START_HEIGHT,start);	
			drawImage3(100,80,YELLOWPONG_WIDTH,YELLOWPONG_HEIGHT,yellowPong);	
			while(!KEY_DOWN_NOW(BUTTON_START));

			blackScreen(WIDTH,HEIGHT);
			spawn_paddles();
			spawn_default();
			spawn_lives();
			lives_text();
		}

		else {
			waitForVblank();
			move_player();
			move_computer();
      		move_ball();
      		check_computer_collision();
      		check_player_collision();
		}

		if(KEY_DOWN_NOW(BUTTON_SELECT)) {
			reset_ball();
			begin = 0;
		}
		else if (KEY_DOWN_NOW(BUTTON_START)) {
			begin = 1;
		}

		if(p.lives == 0) {
			drawImage3(0,0,GAME_OVER_WIDTH,GAME_OVER_HEIGHT,game_over);
			reset_ball();
		}
		else if (p.score == 5) {
			drawImage3(0,0,WIN_WIDTH,WIN_HEIGHT,win);
			reset_ball();
		}
	}
}