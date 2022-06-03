#include <rogue.h>
#include <stdio.h>

const int MAP_HEIGHT = 35;
const int MAP_WIDTH = 150;

unsigned char numFloors = 1;
unsigned char curFloor = 0;

char numMobs = 0;
char numObs = 0;

Player* player;
Floor** floors;


int main(void)
{
	Pos start_pos;

	if(cursesSetup())
	{

		srand(time(NULL));
		initFloors();
		//map = createMapTiles();
		//start_pos = setupMap();
		player = createPlayer(floors[curFloor]->start_pos);
		floors[curFloor]->map[player->entity->pos.y][player->entity->pos.x].occupied = -2;

		gameLoop();

		closeGame();
	}
	else
		endwin();
	return 0;
}