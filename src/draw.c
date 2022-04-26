#include <rogue.h>

void drawMap(Tile** map)
{
	for (int y=0; y<MAP_HEIGHT; y++)
		for (int x=0; x<MAP_WIDTH; x++)
		{
			if (map[y][x].visible)
				mvaddch(y, x, map[y][x].ch | map[y][x].color);
			else if (map[y][x].seen)
				mvaddch(y, x, map[y][x].ch | COLOR_PAIR(SEEN_COLOR));
			else
				mvaddch(y, x, ' ');
		}
}

void drawEntity(Entity* entity)
{
	mvaddch(entity->pos.y, entity->pos.x, entity->ch | entity->color);
}

void drawObs(void)
{
	int y, x;
	for(int i=0; i<numObs; i++)
	{
		y = obList[i]->entity->pos.y;
		x = obList[i]->entity->pos.x;
		//if (map[y][x].visible)
		//	drawEntity(obList[i]->entity);
	}
}

void drawMobs(Floor* floor)
{
	int y, x;
	for (int i=0; i<floor->numMobs; i++)
	{
		y = floor->mobList[i]->entity->pos.y;
		x = floor->mobList[i]->entity->pos.x;
		if (floor->map[y][x].visible)
			drawEntity(floor->mobList[i]->entity);
	}
}

void drawAll(void)
{
	clear();
	drawMap(floors[curFloor]->map);
	//drawObs();
	drawMobs(floors[curFloor]);
	drawEntity(player);
	mvprintw(0, 0, "Floor: %d", curFloor);
	mvprintw(1, 0, "mobList(%p) with sizeMob(%p) = %d, numMob(%p) = %d", floors[curFloor]->mobList, 
					&floors[curFloor]->sizeMobs, floors[curFloor]->sizeMobs, 
					&floors[curFloor]->numMobs, floors[curFloor]->numMobs);
}