#include <rogue.h>
#include <stdio.h>

const int MAP_HEIGHT = 35;
const int MAP_WIDTH = 150;

unsigned char numFloors = 1;
unsigned char curFloor = 0;

char numMobs = 0;
char numObs = 0;

Entity* player;
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
		initFloors();
		//map = createMapTiles();
		//start_pos = setupMap();
		player = createPlayer(floors[curFloor]->start_pos);

		gameLoop();

		closeGame();
	}
	else
		endwin();
	return 0;
}