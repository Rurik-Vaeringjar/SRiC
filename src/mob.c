#include <rogue.h>

void killMob(Entity* mob)
{
	mob->ch = '%';
	mob->color = COLOR_PAIR(CORPSE_COLOR);
	mob->alive = false;
	map[mob->pos.y][mob->pos.x].occupied = false;
}

void moveMob(Entity* mob)
{
	Pos newPos = {mob->pos.y, mob->pos.x};
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
			return;
		map[mob->pos.y][mob->pos.x].occupied = false;
		map[newPos.y][newPos.x].occupied = true;
		mob->pos.y = newPos.y; 
		mob->pos.x = newPos.x;
	}
}

