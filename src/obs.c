#include <rogue.h>

void objectifyMob(char index)
{
	Ob* newOb = calloc(1, sizeof(Ob));
	newOb->entity = mobList[index]->entity;
	appendObList(newOb);
	reduceMobList(floors[curFloor]->map, index);
}

void appendObList(Ob* newOb)
{
	if (numObs == 0)
	{
		obList = calloc(1, sizeof(Ob*));
		obList[0] = newOb;
		obList[0]->index = 0;
		numObs++;
	}
	else
	{
		numObs++;
		char i = numObs-1;
		Ob** tempList = realloc(obList, sizeof(Ob*) * numObs);
		tempList[i] = newOb;
		tempList[i]->index = i;
		obList = tempList;
	}
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