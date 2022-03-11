#include <rogue.h>

void drawMap(void)
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
		if (map[y][x].visible)
			drawEntity(obList[i]->entity);
	}
}

void drawMobs(void)
{
	int y, x;
	for (int i=0; i<numMobs; i++)
	{
		y = mobList[i]->entity->pos.y;
		x = mobList[i]->entity->pos.x;
		if (map[y][x].visible)
			drawEntity(mobList[i]->entity);
	}
}

void drawAll(void)
{
	clear();
	drawMap();
	drawObs();
	drawMobs();
	drawEntity(player);
	
}