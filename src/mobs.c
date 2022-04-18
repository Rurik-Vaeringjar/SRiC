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
		appendMobList(floors[curFloor]->mobList, floors[curFloor]->sizeMobs, floors[curFloor]->numMobs, mob);
}

void initMobList(Mob** mobList, unsigned char* sizeMobs, unsigned char* numMobs)
{
	mobList = calloc(8, sizeof(Mob*));

	void* mSizeMobs = malloc(sizeof(unsigned char));
	sizeMobs = (unsigned char*)mSizeMobs;
	*sizeMobs = 8;

	void* mNumMobs = malloc(sizeof(unsigned char));
	numMobs = (unsigned char*)mNumMobs;
	*numMobs = 0;
}

void appendMobList(Mob** mobList, unsigned char* sizeMobs, unsigned char* numMobs, Mob* newMob)
{
	/*if (numMobs == 0)
	{
		mobList = calloc(1, sizeof(Mob*));
		mobList[0] = newMob;
		mobList[0]->index = 0;
		numMobs++;
	}
	else
	{
		numMobs++;
		char i = numMobs-1;
		Mob** tempList = realloc(mobList, sizeof(Mob*) * numMobs);
		tempList[i] = newMob;
		tempList[i]->index = i;
		mobList = tempList;
	}*/
}

void resizeMobList(Mob** mobList, unsigned char* sizeMobs)
{
	*sizeMobs = *sizeMobs * 2;
	Mob** tempList = realloc(mobList, sizeof(Mob*) * *sizeMobs);
	mobList = tempList;
}


//----------------------------------------------------------------- FREE
void freeMob(Mob* mob)
{
	free(mob->entity);
	free(mob);
}

void reduceMobList(Tile** map, Mob** mobList, unsigned char* numMobs, char index)
{
	/*(*numMobs)--;
	if (index != *numMobs)
	{
		Mob* temp = mobList[index];
		mobList[index] = mobList[*numMobs];
		mobList[index]->index = index;
		map[mobList[index]->entity->pos.y][mobList[index]->entity->pos.x].occupied = index;
		mobList[*numMobs] = temp;	
	}
	free(mobList[*numMobs]);
	Mob** tempList = realloc(mobList, sizeof(Mob*) * numMobs);
	mobList = tempList;*/
}

void clearMobList(void)
{
	//Notice: Do not free(mobList) here
	for (int i=0; i<numMobs; i++)
		freeMob(mobList[i]);
	numMobs = 0;
}
