#include <rogue.h>

const int MAP_HEIGHT = 35;
const int MAP_WIDTH = 150;

char numMobs = 0;
char numObs = 0;

Entity* player;
Mob** mobList;
Ob** obList;
Tile** map;


int main(void)
{
	Pos start_pos;

	if(cursesSetup())
	{
		srand(time(NULL));
		map = createMapTiles();
		start_pos = setupMap();
		player = createPlayer(start_pos);

		gameLoop();

		closeGame();
	}
	else
		endwin();
	return 0;
}