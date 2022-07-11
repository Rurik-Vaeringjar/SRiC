#include <rogue.h>

//----------------------------------------------------------------- ALLOC
Mob* createMob(Pos spawn_pos, Stats base_stats, char ch, uint8_t flags)
{
	Mob* newMob = calloc(1, sizeof(Mob));

	Entity* entity = calloc(1, sizeof(Entity));
	entity->pos.y = spawn_pos.y;
	entity->pos.x = spawn_pos.x;
	entity->ch = ch;
	if (ch == 's')
		entity->color = COLOR_PAIR(SLIME_COLOR);
	else
		entity->color = COLOR_PAIR(MOB_COLOR);
	newMob->entity = entity;


	Stats* stats = calloc(1, sizeof(Stats));
	stats->hp = base_stats.hp;
	stats->MAX_HP = base_stats.MAX_HP;
	stats->armor = base_stats.armor;
	stats->dmg = base_stats.dmg;
	newMob->stats = stats;

	newMob->flags = flags;

	return newMob;
}

void spawnMob(Floor* floor, Pos spawn_pos)
{
	Mob* mob=NULL;

	int roll = rand()%1000;
	Stats base_stats;
	
	//orc
	if (roll > 998)
	{
		base_stats.hp = 30;
		base_stats.MAX_HP = 30;
		base_stats.armor = 2;
		base_stats.dmg = 5;
		mob = createMob(spawn_pos, base_stats, 'T', SLOW);
	}
	else if (roll > 995)
	{
		base_stats.hp = 15;
		base_stats.MAX_HP = 15;
		base_stats.armor = 0;
		base_stats.dmg = 2;
		mob = createMob(spawn_pos, base_stats, 'o', 0);
	}
	else if (roll > 980)
	{
		base_stats.hp = 10;
		base_stats.MAX_HP = 10;
		base_stats.armor = 0;
		base_stats.dmg = 1;
		mob = createMob(spawn_pos, base_stats, 's', 0);
	}
	else if (roll > 975)
	{
		base_stats.hp = 0;
		base_stats.MAX_HP = 0;
		base_stats.armor = 0;
		base_stats.dmg = 0;
		mob = createMob(spawn_pos, base_stats, '%', DEAD | CORPSE);
	}
	
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
		
		if CHK(newMob->flags, DEAD)
			return;
		
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
	free(mob->stats);
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
