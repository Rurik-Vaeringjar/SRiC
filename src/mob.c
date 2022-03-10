#include <rogue.h>

void killMob(Mob* mob)
{
	mob->entity->ch = '%';
	mob->entity->color = COLOR_PAIR(CORPSE_COLOR);
	mob->alive = false;
	map[mob->entity->pos.y][mob->entity->pos.x].occupied = false;
}

void moveMob(Mob* mob)
{
	Pos newPos = {mob->entity->pos.y, mob->entity->pos.x};
	if (map[newPos.y][newPos.x].visible)
	{
		if (newPos.y > player->pos.y)
			newPos.y--;
		else if (newPos.y < player->pos.y)
			newPos.y++;
		else if (newPos.x > player->pos.x)
			newPos.x--;
		else if (newPos.x < player->pos.x)
			newPos.x++;
	}
	else
	{
		newPos.y += rand()%3-1;
		newPos.x += rand()%3-1;
	}

	if (map[newPos.y][newPos.x].walkable)
	{
		if (map[newPos.y][newPos.x].occupied)
		{
		}
		else
		{
			map[mob->entity->pos.y][mob->entity->pos.x].occupied = false;
			map[newPos.y][newPos.x].occupied = true;
			mob->entity->pos.y = newPos.y; 
			mob->entity->pos.x = newPos.x;
		}
	}
}

void mobsTurn()
{
	for (int i=0; i<numMobs; i++)
	{
		if (mobList[i]->alive)
			moveMob(mobList[i]);
	}
}
