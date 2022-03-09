#include <rogue.h>

Entity* createMob(Pos spawn_pos, char ch)
{
	Entity* newMob = calloc(1, sizeof(Entity));

	newMob->pos.y = spawn_pos.y;
	newMob->pos.x = spawn_pos.x;
	newMob->ch = ch;
	newMob->color = COLOR_PAIR(MOB_COLOR);
	newMob->alive = true;

	return newMob;
}

void spawnMob(Pos spawn_pos)
{
	Entity* mob=NULL;

	int roll = rand()%1000;
	//orc
	if (roll > 995)
		mob = createMob(spawn_pos, 'T');
	else if (roll > 980)
		mob = createMob(spawn_pos, 'o');

	if (mob)
		appendMobList(mob);
}

void appendMobList(Entity* newMob)
{
	if (numMobs == 0)
	{
		mobList = calloc(1, sizeof(Entity*));
		mobList[0] = newMob;
		numMobs++;
	}
	else
	{
		numMobs++;
		Entity** tempList = realloc(mobList, sizeof(Entity*) * numMobs);
		tempList[numMobs-1] = newMob;
		mobList = tempList;
	}
}

void reduceMobList(int index)
{
	numMobs--;
	if (index != numMobs)
	{
		Entity* temp = mobList[index];
		mobList[index] = mobList[numMobs];
		mobList[numMobs] = temp;	
	}
	free(mobList[numMobs]);
	Entity** tempList = realloc(mobList, sizeof(Entity*) * numMobs);
	mobList = tempList;
}

void clearMobList(void)
{
	//Notice: Do not free(mobList) here
	for (int i=0; i<numMobs; i++)
		free(mobList[i]);
	numMobs = 0;
}
