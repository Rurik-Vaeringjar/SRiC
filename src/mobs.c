#include <rogue.h>

//----------------------------------------------------------------- ALLOC
Mob* createMob(Pos spawn_pos, Stats start_stats, char ch)
{
	Mob* newMob = calloc(1, sizeof(Mob));

	newMob->entity = calloc(1, sizeof(Entity));
	newMob->entity->pos.y = spawn_pos.y;
	newMob->entity->pos.x = spawn_pos.x;
	newMob->entity->ch = ch;
	if (ch == 's')
		newMob->entity->color = COLOR_PAIR(SLIME_COLOR);
	else
		newMob->entity->color = COLOR_PAIR(MOB_COLOR);
	return newMob;
}

void spawnMob(Floor* floor, Pos spawn_pos)
{
	Mob* mob=NULL;

	int roll = rand()%1000;
	Stats base_stats;
	
	//orc
	if (roll > 998)
		mob = createMob(spawn_pos, base_stats, 'T');
	else if (roll > 995)
		mob = createMob(spawn_pos, base_stats, 'o');
	else if (roll > 980)
		mob = createMob(spawn_pos, base_stats, 's');

	if (mob)
		appendMobList(floor, mob);
}

void initMobList(Floor* floor)
{
	floor->mobList = calloc(8, sizeof(Mob*));
	floor->sizeMobs = 8;
	floor->numMobs = 0;
}

void appendMobList(Floor* floor, Mob* newMob)
{
		floor->numMobs++;
		if (floor->numMobs > floor->sizeMobs)
			resizeMobList(floor, 1);
		
		char i = floor->numMobs-1;
		floor->mobList[i] = newMob;
		floor->mobList[i]->index = i;
		floor->map[newMob->entity->pos.y][newMob->entity->pos.x].occupied = i;
}

void resizeMobList(Floor* floor, char mod)
{
	floor->sizeMobs = floor->sizeMobs + (8*mod);
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
	
	if (floor->numMobs%8 == 0)
		resizeMobList(floor, -1);
}

void freeMobList(Floor* floor)
{
	//Notice: Do not free(mobList) here
	for (int i=0; i<floor->numMobs; i++)
		freeMob(floor->mobList[i]);
	free(floor->mobList);
}
