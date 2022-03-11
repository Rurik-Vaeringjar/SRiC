#include <rogue.h>

//----------------------------------------------------------------- ALLOC
Mob* createMob(Pos spawn_pos, char ch)
{
	Mob* newMob = calloc(1, sizeof(Mob));

	newMob->entity = calloc(1, sizeof(Entity));
	newMob->entity->pos.y = spawn_pos.y;
	newMob->entity->pos.x = spawn_pos.x;
	newMob->entity->ch = ch;
	newMob->entity->color = COLOR_PAIR(MOB_COLOR);
	newMob->alive = true;

	return newMob;
}

void spawnMob(Pos spawn_pos)
{
	Mob* mob=NULL;

	int roll = rand()%1000;
	//orc
	if (roll > 995)
		mob = createMob(spawn_pos, 'T');
	else if (roll > 980)
		mob = createMob(spawn_pos, 'o');

	if (mob)
		appendMobList(mob);
}

void appendMobList(Mob* newMob)
{
	if (numMobs == 0)
	{
		mobList = calloc(1, sizeof(Mob*));
		mobList[0] = newMob;
		numMobs++;
	}
	else
	{
		numMobs++;
		Mob** tempList = realloc(mobList, sizeof(Mob*) * numMobs);
		tempList[numMobs-1] = newMob;
		mobList = tempList;
	}
}

//----------------------------------------------------------------- FREE
void freeMob(Mob* mob)
{
	free(mob->entity);
	free(mob);
}

void reduceMobList(int index)
{
	numMobs--;
	if (index != numMobs)
	{
		Mob* temp = mobList[index];
		mobList[index] = mobList[numMobs];
		mobList[numMobs] = temp;	
	}
	free(mobList[numMobs]);
	Mob** tempList = realloc(mobList, sizeof(Mob*) * numMobs);
	mobList = tempList;
}

void clearMobList(void)
{
	//Notice: Do not free(mobList) here
	for (int i=0; i<numMobs; i++)
		freeMob(mobList[i]);
	numMobs = 0;
}
