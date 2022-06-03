#include <rogue.h>
#include <stdio.h>

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
	
	initMobList(floor);
	initObList(floor);

	Pos* pos; 
	pos = setupMap(floor);
	floor->start_pos.y = pos[0].y;
	floor->start_pos.x = pos[0].x;
	floor->end_pos.y = pos[1].y;
	floor->end_pos.x = pos[1].x;
	free(pos);

	return floor;
}

void newFloor(void)
{
	numFloors++;
	Floor** tempFloors = realloc(floors, sizeof(Floor*) * numFloors);
	tempFloors[curFloor] = createFloor();
	floors = tempFloors;
}

void nextFloor(void)
{
	if (curFloor == 254)
		return;

	clearFOV(floors[curFloor]->map, player->entity);

	curFloor++;
	if (curFloor == numFloors)
		newFloor();
	
	player->entity->pos.y = floors[curFloor]->start_pos.y;
	player->entity->pos.x = floors[curFloor]->start_pos.x;
}

void prevFloor(void)
{
	if (curFloor == 0)
		return;

	clearFOV(floors[curFloor]->map, player->entity);

	curFloor--;

	player->entity->pos.y = floors[curFloor]->end_pos.y;
	player->entity->pos.x = floors[curFloor]->end_pos.x;
}

void freeFloors(void)
{
	for (int i=0; i<numFloors; i++)
	{
		freeMap(floors[i]->map);
		freeMobList(floors[i]);
		freeObList(floors[i]);
	}
}