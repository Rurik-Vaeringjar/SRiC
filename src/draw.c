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

void drawEntity(Entity* entity, bool visible)
{
		int color;
		if (visible)
			color = entity->color;
		else
			color = COLOR_PAIR(SEEN_COLOR);

		mvaddch(entity->pos.y, entity->pos.x, entity->ch | color);
}

void drawObs(Floor* floor)
{
	int y, x;
	for(int i=floor->numObs-1; i>=0; i--)
	{
		y = floor->obList[i]->entity->pos.y;
		x = floor->obList[i]->entity->pos.x;
		if (floor->map[y][x].visible)
			drawEntity(floor->obList[i]->entity, true);
		else if (floor->map[y][x].seen)
			drawEntity(floor->obList[i]->entity, false);
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
			drawEntity(floor->mobList[i]->entity, true);
	}
}

void drawUI(void)
{
	mvprintw(0, 0, "Floor: %d", curFloor+1);
	/*
	mvprintw(1, 0, "mobList(%p) with sizeMob(%p) = %d, numMob(%p) = %d", floors[curFloor]->mobList, 
					&floors[curFloor]->sizeMobs, floors[curFloor]->sizeMobs, 
					&floors[curFloor]->numMobs, floors[curFloor]->numMobs);
	mvprintw(2, 0, "obList(%p) with sizeOb(%p) = %d, numOb(%p) = %d", floors[curFloor]->obList, 
					&floors[curFloor]->sizeObs, floors[curFloor]->sizeObs, 
					&floors[curFloor]->numObs, floors[curFloor]->numObs);
	*/
	if CHK(floors[curFloor]->map[player->pos.y][player->pos.x].obFlags, STAIRS)
		mvprintw(1, 0, "stairs");
	else if CHK(floors[curFloor]->map[player->pos.y][player->pos.x].obFlags, CORPSE)
		mvprintw(1, 0, "corpse");
}

void drawAll(void)
{
	clear();
	drawMap(floors[curFloor]->map);
	drawObs(floors[curFloor]);
	drawMobs(floors[curFloor]);
	drawUI();
	drawEntity(player, true);
}