#include <rogue.h>

void initFloors(void)
{
	floors = calloc(1, sizeof(Floor*));
	Floor* floor = createFloor();
	floors[0] = floor;
}

Floor* createFloor(void)
{
	Floor* floor = calloc(1, sizeof(Floor));
	floor->map = createMapTiles();
	floor->start_pos = setupMap(floor->map);

	return floor;
}

void newFloor(void)
{
	numFloors++;
	curFloor++;
	Floor** tempFloors = realloc(floors, sizeof(Floor*) * numFloors);
	tempFloors[curFloor] = createFloor();
	floors = tempFloors;
}

void freeFloors(void)
{
	for (int i=0; i<numFloors; i++)
	{
		freeMap(floors[i]->map);
	}
}