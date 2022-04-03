#include <rogue.h>

const int MAP_HEIGHT = 35;
const int MAP_WIDTH = 150;

unsigned char numMobs = 0;
unsigned char numObs = 0;

unsigned char numFloors = 1;
unsigned char currentFloor = 0;

Entity* player;
Mob** mobList;
Ob** obList;
Tile** map;
Floor** floors;


int main(void)
{
	Pos start_pos;

	if(cursesSetup())
	{

		srand(time(NULL));
		map = createMapTiles();
		start_pos = setupMap();
		player = createPlayer(start_pos);
		initFloors();

		gameLoop();

		closeGame();
	}
	else
		endwin();
	return 0;
}