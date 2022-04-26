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

void spawnMob(Floor* floor, Pos spawn_pos)
{
	Mob* mob=NULL;

	int roll = rand()%1000;
	//orc
	if (roll > 995)
		mob = createMob(spawn_pos, 'T');
	else if (roll > 980)
		mob = createMob(spawn_pos, 'o');

	if (mob)
		appendMobList(floor, mob);
}

void initMobList(Floor* floor)
{
	floor->mobList = calloc(8, sizeof(Mob*));
	floor->sizeMobs = 8;
	floor->numMobs = 0;

	//printf("sizeMobs = %d and numMobs = %d\n", *(floor->sizeMobs), *(floor->numMobs));
	//printf("%p, %p, and %p\n", floor->mobList, floor->sizeMobs, floor->numMobs);
}

void appendMobList(Floor* floor, Mob* newMob)
{
		floor->numMobs++;
		if (floor->numMobs > floor->sizeMobs)
			resizeMobList(floor);
		
		char i = floor->numMobs-1;
		floor->mobList[i] = newMob;
		floor->mobList[i]->index = i;
}

void resizeMobList(Floor* floor)
{
	floor->sizeMobs = floor->sizeMobs +8;
	Mob** tempList = realloc(floor->mobList, sizeof(Mob*) * floor->sizeMobs);
	floor->mobList = tempList;
}
//----------------------------------------------------------------- FREE
void freeMob(Mob* mob)
{
	free(mob->entity);
	free(mob);
}

void reduceMobList(Floor* floor, char index)
{
	floor->numMobs--;
	if (index != floor->numMobs)
	{
		Mob* temp = floor->mobList[index];
		floor->mobList[index] = floor->mobList[floor->numMobs];
		floor->mobList[index]->index = index;
		floor->map[floor->mobList[index]->entity->pos.y][floor->mobList[index]->entity->pos.x].occupied = index;
		floor->mobList[floor->numMobs] = temp;
	}
	free(floor->mobList[floor->numMobs]);
}

void freeMobList(Floor* floor)
{
	//Notice: Do not free(mobList) here
	for (int i=0; i<floor->numMobs; i++)
		freeMob(floor->mobList[i]);
	free(floor->mobList);
}
