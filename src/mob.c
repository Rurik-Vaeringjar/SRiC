#include <rogue.h>

void killMob(Tile** map, Mob* mob)
{
	if (mob->entity->ch == 's')
		mob->entity->color = COLOR_PAIR(DEAD_SLIME_COLOR);
	else
		mob->entity->color = COLOR_PAIR(CORPSE_COLOR);
	mob->entity->ch = '%';
	map[mob->entity->pos.y][mob->entity->pos.x].occupied = -1;
}

void moveMob(Tile** map, Mob* mob)
{
	Pos newPos = {mob->entity->pos.y, mob->entity->pos.x};
	if (CHK(map[newPos.y][newPos.x].attrFlags, VISIBLE))
	{
		int dy = player->entity->pos.y - newPos.y;
		int dx = player->entity->pos.x - newPos.x;

		int abs_dy = abs(dy);
		int abs_dx = abs(dx);

		if (abs_dy > 1)
		{
			dy = (dy/abs_dy);
			newPos.y += dy;
		}
		if (abs_dx > 1)
		{
			dx = (dx/abs_dx);
			newPos.x += dx;
		}
	}
	else
	{
		newPos.y += rand()%3-1;
		newPos.x += rand()%3-1;
	}

	if (CHK(map[newPos.y][newPos.x].attrFlags, WALKABLE))
	{
		if (map[newPos.y][newPos.x].occupied == -1)
		{
			map[mob->entity->pos.y][mob->entity->pos.x].occupied = -1;
			mob->entity->pos.y = newPos.y;
			mob->entity->pos.x = newPos.x;
			map[newPos.y][newPos.x].occupied = mob->index;
		}
		else
		{
			
		}
	}
}

void mobsTurn()
{
	for (int i=0; i<floors[curFloor]->numMobs; i++)
	{
		moveMob(floors[curFloor]->map, floors[curFloor]->mobList[i]);
	}
}
