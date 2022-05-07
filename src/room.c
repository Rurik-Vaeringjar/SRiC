#include <rogue.h>
Room createRoom(int y, int x, int height, int width)
{
	Room newRoom;

	newRoom.pos.y = y;
	newRoom.pos.x = x;
	newRoom.height = height;
	newRoom.width = width;
	newRoom.cntr.y = y + height/2;
	newRoom.cntr.x = x + width/2;

	return newRoom;
}

void addRoom(Floor* floor, Room room)
{
	for (int y=room.pos.y; y<room.pos.y+room.height; y++)
		for (int x=room.pos.x; x<room.pos.x+room.width; x++)
			if(y<MAP_HEIGHT && y>0 && x<MAP_WIDTH && x>0)
			{
				floor->map[y][x].ch = '.';
				SET(floor->map[y][x].attrFlags, WALKABLE|TRANSPARENT);

				spawnMob(floor, (Pos){y, x});
			}
			else
				mvaddch(1, 1, '!');
}

void connectRoomsCenter(Tile** map, Pos cntrA, Pos cntrB)
{
	Pos temp;
	temp.y = cntrA.y;
	temp.x = cntrA.x;
	
	while(true)
	{
		if (abs((temp.x-1)-cntrB.x) < abs(temp.x-cntrB.x))
			temp.x--;
		else if (abs((temp.x+1)-cntrB.x) < abs(temp.x-cntrB.x))
			temp.x++;
		else if (abs((temp.y-1)-cntrB.y) < abs(temp.y-cntrB.y))
			temp.y--;
		else if (abs((temp.y+1)-cntrB.y) < abs(temp.y-cntrB.y))
			temp.y++;
		else
			break;

		map[temp.y][temp.x].ch = '.';
		SET(map[temp.y][temp.x].attrFlags, WALKABLE|TRANSPARENT);
	}
}