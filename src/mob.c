#include <rogue.h>

void killMob(Mob* mob)
{
	mob->entity->ch = '%';
	mob->entity->color = COLOR_PAIR(CORPSE_COLOR);
	map[mob->entity->pos.y][mob->entity->pos.x].occupied = -1;
}

void moveMob(Mob* mob)
{
	Pos newPos = {mob->entity->pos.y, mob->entity->pos.x};
	if (map[newPos.y][newPos.x].visible)
	{
		/*int dy = player->pos.y - newPos.y;
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
				newPos.x++;*/
		int dy = player->pos.y - newPos.y;
		int dx = player->pos.x - newPos.x;

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

	if (map[newPos.y][newPos.x].walkable)
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
	for (int i=0; i<numMobs; i++)
	{
		moveMob(mobList[i]);
	}
}
