#include <rogue.h>

bool cursesSetup(void)
{
	initscr();
	noecho();
	curs_set(0);

	if (has_colors())
	{
		start_color();

		init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
		init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
		init_pair(MOB_COLOR, COLOR_YELLOW, COLOR_BLACK);
		init_pair(SLIME_COLOR, COLOR_GREEN, COLOR_BLACK);
		init_pair(CORPSE_COLOR, COLOR_RED, COLOR_BLACK);
		init_pair(DEAD_SLIME_COLOR, COLOR_BLACK, COLOR_GREEN);

		return true;
	}
	else
	{
		mvprintw(20, 50, "Your system doesn't support color. Can't start game!");
	   	getch();
	 	return false;
	}
}

void gameLoop(void)
{
	char ch;

	makeFOV(floors[curFloor]->map, player->entity);
	drawAll();

	while(ch = getch())
	{
		if (ch==27)
			break;		

		//player's turn
		handleInput(ch);

		drawAll();

		//mob's turn
		mobsTurn();

		drawAll();
	}
}

void closeGame(void)
{
	endwin();
	freePlayer();
	freeFloors();
}