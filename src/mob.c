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
	if (mob->entity->ch == 'T' && (rand()%2))
		return;

	Pos newPos = {mob->entity->pos.y, mob->entity->pos.x};
	if (CHK(map[newPos.y][newPos.x].attrFlags, VISIBLE))
	{
		int dy = player->entity->pos.y - newPos.y;
		int dx = player->entity->pos.x - newPos.x;

		int abs_dy = abs(dy);
		int abs_dx = abs(dx);

		if (abs_dy > 0)
		{
			dy = (dy/abs_dy);
			newPos.y += dy;
		}
		if (abs_dx > 0)
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
		char occupied = map[newPos.y][newPos.x].occupied;
		if (occupied == -1)
		{
			map[mob->entity->pos.y][mob->entity->pos.x].occupied = -1;
			mob->entity->pos.y = newPos.y;
			mob->entity->pos.x = newPos.x;
			map[newPos.y][newPos.x].occupied = mob->index;
		}
		else if (occupied == -2)
		{
			if(attack(mob->stats, player->stats))
			{
				player->stats->hp = 1;
			}
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
