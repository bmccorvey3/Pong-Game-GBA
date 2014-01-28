//Brent McCorvey

//Class that creates the "objects"

#ifndef elements
#define elements

struct Player {
	int r;
	int c;
	int width;
	int height;
	int lives;
	int score;
};

struct Computer {
	int r;
	int c;
	int width;
	int height;
};

struct Player p;
struct Computer comp;

void spawn_paddles();
void spawn_lives();
void spawn_player();
void spawn_default();
void move_player();
void move_computer();
void reset_ball();
void move_ball();
void check_player_collision();
void check_computer_collision();
void lives_text();

#endif