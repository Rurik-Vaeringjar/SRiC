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
		init_pair(CORPSE_COLOR, COLOR_RED, COLOR_BLACK);

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
	int ch;

	makeFOV(player);
	drawAll();

	while(ch = getch())
	{
		if (ch=='q')
			break;		
		
		//mob's turn
		mobsTurn();

		//player's turn
		handleInput(ch);

		drawAll();
	}
}

void closeGame(void)
{
	endwin();
	free(player);
	freeMap();
	clearObList();
	free(obList);
	clearMobList();
	free(mobList);
}