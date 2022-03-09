#include <rogue.h>

const int MAP_HEIGHT = 35;
const int MAP_WIDTH = 150;

int numMobs = 0;

Entity* player;
Entity** mobList;
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