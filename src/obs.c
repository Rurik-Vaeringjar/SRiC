#include <rogue.h>

void objectifyMob(char index)
{
	Ob* newOb = calloc(1, sizeof(Ob));
	newOb->entity = floors[curFloor]->mobList[index]->entity;
	SET(newOb->flags, CORPSE);
	appendObList(floors[curFloor], newOb);
	reduceMobList(floors[curFloor], index);
}

void initObList(Floor* floor)
{
	floor->obList = calloc(8, sizeof(Ob*));
	floor->sizeObs = 8;
	floor->numObs = 0;
}

void appendObList(Floor* floor, Ob* newOb)
{
	floor->numObs++;
		if (floor->numObs > floor->sizeObs)
			resizeObList(floor);
		
		char i = floor->numObs-1;
		SET(floor->map[newOb->entity->pos.y][newOb->entity->pos.x].obFlags, newOb->flags);
		floor->obList[i] = newOb;
		floor->obList[i]->index = i;
		
}

void resizeObList(Floor* floor)
{
	floor->sizeObs = floor->sizeObs +8;
	Ob** tempList = realloc(floor->obList, sizeof(Ob*) * floor->sizeObs);
	floor->obList = tempList;
}

void freeOb(Ob* ob)
{
	free(ob->entity);
	free(ob);
}

void reduceObList(Floor* floor, char index)
{
	/*floor->numObs--;
	if (index != floor->numObs)
	{
		Ob* temp = obList[index];
		obList[index] = obList[nObs];
		obList[index]->index = index;
		obList[nObs] = temp;	
	}
	freeOb(obList[numObs]);
	Ob** tempList = realloc(obList, sizeof(Ob*) * numObs);
	obList = tempList;*/
}

void freeObList(Floor* floor)
{
	//Notice: Do not free(obList) here
	for (int i=0; i<floor->numObs; i++)
		freeOb(floor->obList[i]);
	free(floor->obList);
}