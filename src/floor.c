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

void saveFloor(void)
{
	floors[currentFloor]->numMobs = numMobs;
	floors[currentFloor]->numObs = numObs;
}

void loadFloor(unsigned char index)
{
	saveFloor();
	map = floors[index]->map;
	mobList = floors[index]->mobList;
	numMobs = floors[index]->numMobs;
	obList = floors[index]->obList;
	numObs = floors[index]->numObs;
	currentFloor = index;
}