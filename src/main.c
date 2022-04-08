#include <rogue.h>
#include <stdio.h>

const int MAP_HEIGHT = 35;
const int MAP_WIDTH = 150;

unsigned char *numMobs; //= 0;
unsigned char *numObs;

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
	unsigned char nMobs = 0;
	numMobs = &nMobs;
	
	unsigned char nObs = 0;
	numObs = &nObs;

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