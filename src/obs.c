#include <rogue.h>

void objectifyMob(int index)
{
	
}

void appendObList(Ob* newOb)
{
	if (numObs == 0)
	{
		obList = calloc(1, sizeof(Ob*));
		obList[0] = newOb;
		numObs++;
	}
	else
	{
		numObs++;
		Ob** tempList = realloc(obList, sizeof(Ob*) * numObs);
		tempList[numObs-1] = newOb;
		obList = tempList;
	}
}

void freeOb(Ob* ob)
{
	free(ob->entity);
	free(ob);
}

void reduceObList(int index)
{
	numObs--;
	if (index != numObs)
	{
		Ob* temp = obList[index];
		obList[index] = obList[numObs];
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