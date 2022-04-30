#include <rogue.h>

Tile** createMapTiles(void)
{
	Tile** tiles = calloc(MAP_HEIGHT, sizeof(Tile*));

	for (int y=0; y<MAP_HEIGHT; y++)
	{
		tiles[y] = calloc(MAP_WIDTH, sizeof(Tile));
		for(int x=0; x<MAP_WIDTH; x++)
		{
			tiles[y][x].ch = '#';
			tiles[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
			tiles[y][x].walkable = false;
			tiles[y][x].transparent = false;
			tiles[y][x].visible = false;
			tiles[y][x].seen = false;
			tiles[y][x].occupied = -1;
		}
	}

	return tiles;
}

Pos* setupMap(Floor* floor)
{
	int y, x, height, width, n_rooms;
	n_rooms = rand()%11 + 10;
	Room* rooms = calloc(n_rooms, sizeof(Room));
	Pos* pos = calloc(2, sizeof(Pos));

	for (int i=0; i<n_rooms; i++)
	{
		y = rand()%(MAP_HEIGHT-10)+1;
		x = rand()%(MAP_WIDTH-20)+1;
		height = rand()%7 + 3;
		width = rand()%15 + 5;
		rooms[i] = createRoom(y, x, height, width);
		addRoom(floor, rooms[i]);
	
		if (i > 0)
			connectRoomsCenter(floor->map, rooms[i-1].cntr, rooms[i].cntr);
	}

	pos[0].y = rooms[0].cntr.y;
	pos[0].x = rooms[0].cntr.x;

	pos[1].y = rooms[n_rooms-1].cntr.y;
	pos[1].x = rooms[n_rooms-1].cntr.x;

	Ob* newOb;
	newOb = createStairs(pos[1], '>');
	floor->obList[0] = newOb;
	floor->obList[0]->index = 0;
	SET(floor->map[newOb->entity->pos.y][newOb->entity->pos.x].obFlags, newOb->flags);

	if (curFloor > 0)
	{
		newOb = createStairs(pos[0], '<');
		floor->obList[1] = newOb;
		floor->obList[1]->index = 1;
		SET(floor->map[newOb->entity->pos.y][newOb->entity->pos.x].obFlags, newOb->flags);
	}

	free(rooms);

	return pos;
}

void freeMap(Tile** map)
{
	for(int y=0; y<MAP_HEIGHT; y++)
		free(map[y]);
	free(map);
}