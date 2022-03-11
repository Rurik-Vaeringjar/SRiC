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
		int dy = player->pos.y - newPos.y;
		int dx = player->pos.x - newPos.x;

		if (abs(dy) > abs(dx))
			if (dy < 0)
				newPos.y--;
			else
				newPos.y++;
		else
			if (dx < 0)
				newPos.x--;
			else
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
