#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>

const char* starchar[] = {" ","·", "∙", "•", "☼"};

struct stars {
	uint8_t state;
	uint8_t y;
	uint8_t x;
	uint16_t turns_left;
};
	
#define STARCOUNT 50
struct stars sky[STARCOUNT];

void update_star(int i) {

	if (i < 0) return;
	mvaddstr(sky[i].y,sky[i].x,starchar[sky[i].state]);
	refresh();
	return;
}

int spawn_star() {
	
	for (int i=0; i< STARCOUNT; i++) {
		if (sky[i].state) continue;

		sky[i].x = rand() % COLS;
		sky[i].y = rand() % LINES;
		sky[i].state = 1;
		sky[i].turns_left = rand() % 256;

		return i;
	}
	return -1;
}

int main(int argc, char** argv) {
	
	setlocale(LC_ALL,"");

	initscr();
	cbreak();
	noecho();
	curs_set(0);

	nodelay(stdscr, 1);

	while (getch() == ERR) {

	for (int i=0; i< STARCOUNT; i++) {
		if (!sky[i].state) continue;

		sky[i].turns_left--;
		if (sky[i].turns_left == 0) {

			sky[i].state++;
			if ((sky[i].state > 4) || (rand() % 2)) sky[i].state = 0; else
				sky[i].turns_left = 16 >> (sky[i].state);
			update_star(i);
		}
	}

	if (!(rand() % 8)) update_star(spawn_star());

	usleep(50000);

	}	

	endwin();
	return 0;
}
