#include <rogue.h>

void drawMap(Tile** map)
{
	for (int y=0; y<MAP_HEIGHT; y++)
		for (int x=0; x<MAP_WIDTH; x++)
		{
			if (CHK(map[y][x].attrFlags, VISIBLE))
				mvaddch(y, x, map[y][x].ch | map[y][x].color);
			else if (CHK(map[y][x].attrFlags, SEEN))
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

void drawPlayer()
{
	mvprintw(1, 0, "Health: %d/%d", player->stats->hp, player->stats->MAX_HP);
	mvprintw(2, 0, "Armor: %d", player->stats->armor);
	mvprintw(3, 0, "Damage: %d", player->stats->dmg);

	drawEntity(player->entity, true);
}

void drawObs(Floor* floor)
{
	int y, x;
	for(int i=floor->numObs-1; i>=0; i--)
	{
		y = floor->obList[i]->entity->pos.y;
		x = floor->obList[i]->entity->pos.x;
		if (CHK(floor->map[y][x].attrFlags, VISIBLE))
			drawEntity(floor->obList[i]->entity, true);
		else if (CHK(floor->map[y][x].attrFlags, SEEN))
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
		if (CHK(floor->map[y][x].attrFlags, VISIBLE))
			drawEntity(floor->mobList[i]->entity, true);
	}
}

void drawUI(void)
{
	mvprintw(0, 0, "Floor: %d", curFloor+1);
	
	mvprintw(36, 0, "mobList(%p) with sizeMob(%p) = %d, numMob(%p) = %d", floors[curFloor]->mobList, 
					&floors[curFloor]->sizeMobs, floors[curFloor]->sizeMobs, 
					&floors[curFloor]->numMobs, floors[curFloor]->numMobs);
	mvprintw(37, 0, "obList(%p) with sizeOb(%p) = %d, numOb(%p) = %d", floors[curFloor]->obList, 
					&floors[curFloor]->sizeObs, floors[curFloor]->sizeObs, 
					&floors[curFloor]->numObs, floors[curFloor]->numObs);

	if CHK(floors[curFloor]->map[player->entity->pos.y][player->entity->pos.x].obFlags, STAIRS)
		mvprintw(4, 0, "stairs");
	else if CHK(floors[curFloor]->map[player->entity->pos.y][player->entity->pos.x].obFlags, CORPSE)
		mvprintw(4, 0, "corpse");

}

void drawAll(void)
{
	clear();
	drawMap(floors[curFloor]->map);
	drawObs(floors[curFloor]);
	drawMobs(floors[curFloor]);
	drawUI();
	drawPlayer();
}