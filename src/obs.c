#include <rogue.h>

void objectifyMob(char index)
{
	Ob* newOb = calloc(1, sizeof(Ob));
	newOb->entity = mobList[index]->entity;
	appendObList(newOb);
	reduceMobList(index);
}

void appendObList(Ob* newOb)
{
	if (*numObs == 0)
	{
		obList = calloc(1, sizeof(Ob*));
		obList[0] = newOb;
		obList[0]->index = 0;
		(*numObs)++;
	}
	else
	{
		(*numObs)++;
		char i = *numObs-1;
		Ob** tempList = realloc(obList, sizeof(Ob*) * *numObs);
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
	unsigned char nObs = *numObs;
	nObs--;
	if (index != nObs)
	{
		Ob* temp = obList[index];
		obList[index] = obList[nObs];
		obList[index]->index = index;
		obList[nObs] = temp;	
	}
	freeOb(obList[nObs]);
	Ob** tempList = realloc(obList, sizeof(Ob*) * nObs);
	obList = tempList;
	*numObs = nObs;
}

void clearObList(Ob** obList, unsigned char nObs)
{
	//Notice: Do not free(obList) here
	for (int i=0; i<nObs; i++)
		freeOb(obList[i]);
	numObs = 0;
}