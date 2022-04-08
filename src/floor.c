#include <rogue.h>

void initFloors(void)
{
	floors = calloc(1, sizeof(Floor*));
	Floor* floor = calloc(1, sizeof(Floor));
	floor->map = map;
	floor->mobList = mobList;
	floor->numMobs = numMobs;
	floor->obList = obList;
	floor->numObs = numObs;
	floors[0] = floor;
}

void addFloor(Floor* floor)
{
	numFloors++;
	unsigned char i = numFloors-1;
	Floor** tempFloors = realloc(floors, sizeof(Floor*) * numFloors);
	tempFloors[i] = floor;
	floors = tempFloors;
}

Floor* createFloor(void)
{
	Floor* floor = calloc(1, sizeof(Floor));
	
	Mob** newMobList;
	floor->mobList = newMobList;
	unsigned char newNumMobs = 0;
	floor->numMobs = &newNumMobs;

	Ob** newObList;
	floor->obList = newObList;
	unsigned char newNumObs = 0;
	floor->numObs = &newNumObs;

	floor->map = createMapTiles();

	return floor;
}

void newFloor(void)
{
	Floor* floor = createFloor();
	
	map = floor->map;
	mobList = floor->mobList;
	numMobs = floor->numMobs;
	obList = floor->obList;
	numObs = floor->numObs;

	floor->entry = setupMap();
	player->pos.y = floor->entry.y;
	player->pos.x = floor->entry.x;
	makeFOV(player);

	currentFloor++;
	addFloor(floor);

}

void loadFloor(unsigned char index)
{
	map = floors[index]->map;
	mobList = floors[index]->mobList;
	numMobs = floors[index]->numMobs;
	obList = floors[index]->obList;
	numObs = floors[index]->numObs;
	currentFloor = index;
}

void freeFloors(void)
{
	for (int i=0; i<numFloors; i++)
	{	
		clearMobList(floors[i]->mobList, *(floors[i]->numMobs));
		clearObList(floors[i]->obList, *(floors[i]->numObs));
		freeMap(floors[i]->map);
		free(floors[i]);
	}
	free(floors);
}