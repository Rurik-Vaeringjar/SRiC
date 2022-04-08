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
	if (*numMobs == 0)
	{
		mobList = calloc(1, sizeof(Mob*));
		mobList[0] = newMob;
		mobList[0]->index = 0;
		(*numMobs)++;
	}
	else
	{
		(*numMobs)++;
		char i = *numMobs-1;
		Mob** tempList = realloc(mobList, sizeof(Mob*) * *numMobs);
		tempList[i] = newMob;
		tempList[i]->index = i;
		mobList = tempList;
	}
}

//----------------------------------------------------------------- FREE
void freeMob(Mob* mob)
{
	free(mob->entity);
	free(mob);
}

void reduceMobList(char index)
{
	unsigned char nMobs = *numMobs;
	nMobs--;
	if (index != nMobs)
	{
		Mob* temp = mobList[index];
		mobList[index] = mobList[nMobs];
		mobList[index]->index = index;
		map[mobList[index]->entity->pos.y][mobList[index]->entity->pos.x].occupied = index;
		mobList[nMobs] = temp;	
	}
	free(mobList[nMobs]);
	Mob** tempList = realloc(mobList, sizeof(Mob*) * nMobs);
	mobList = tempList;
	*numMobs = nMobs;
}

void clearMobList(Mob** mobList, unsigned char nMobs)
{
	//Notice: Do not free(mobList) here
	for (int i=0; i<nMobs; i++)
		freeMob(mobList[i]);
}
