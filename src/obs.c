#include <rogue.h>

void objectifyMob(char index)
{
	Ob* newOb = calloc(1, sizeof(Ob));
	newOb->entity = floors[curFloor]->mobList[index]->entity;
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
}

void freeOb(Ob* ob)
{
	free(ob->entity);
	free(ob);
}

void reduceObList(char index)
{
	numObs--;
	if (index != numObs)
	{
		Ob* temp = obList[index];
		obList[index] = obList[numObs];
		obList[index]->index = index;
		obList[numObs] = temp;	
	}
	freeOb(obList[numObs]);
	Ob** tempList = realloc(obList, sizeof(Ob*) * numObs);
	obList = tempList;
}

void clearObList(void)
{
	//Notice: Do not free(obList) here
	for (int i=0; i<numObs; i++)
		freeOb(obList[i]);
	numObs = 0;
}