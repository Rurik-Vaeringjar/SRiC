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

Pos setupMap(Tile** map)
{
	int y, x, height, width, n_rooms;
	n_rooms = rand()%11 + 10;
	Room* rooms = calloc(n_rooms, sizeof(Room));
	Pos start_pos;

	for (int i=0; i<n_rooms; i++)
	{
		y = rand()%(MAP_HEIGHT-10)+1;
		x = rand()%(MAP_WIDTH-20)+1;
		height = rand()%7 + 3;
		width = rand()%15 + 5;
		rooms[i] = createRoom(y, x, height, width);
		addRoom(map, rooms[i]);
	
		if (i > 0)
			connectRoomsCenter(map, rooms[i-1].cntr, rooms[i].cntr);

	}

	start_pos.y = rooms[0].cntr.y;
	start_pos.x = rooms[0].cntr.x;

	free(rooms);

	return start_pos;
}

void freeMap(Tile** map)
{
	for(int y=0; y<MAP_HEIGHT; y++)
		free(map[y]);
	free(map);
}