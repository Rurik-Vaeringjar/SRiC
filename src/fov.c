#include <rogue.h>

void makeFOV(Tile** map, Entity* player)
{
	int y, x, distance, rad=15;
	Pos target;

	SET(map[player->pos.y][player->pos.x].attrFlags, VISIBLE|SEEN);

	for (y=player->pos.y-rad; y<player->pos.y+rad; y++)
		for(x=player->pos.x-rad; x<player->pos.x+rad; x++)
		{
			target.y = y;
			target.x = x;
			distance = getDistance(player->pos, target);

			if(distance<rad)
				if(isInMap(y, x) && lineOfSight(map, player->pos, target))
					SET(map[y][x].attrFlags, VISIBLE|SEEN);
		}
}

void clearFOV(Tile** map, Entity* player)
{
	int y, x, rad=15;
	for (y=player->pos.y-rad; y<player->pos.y+rad; y++)
		for(x=player->pos.x-rad; x<player->pos.x+rad; x++)
			if(isInMap(y, x))
				CLR(map[y][x].attrFlags, VISIBLE);

}

int getDistance(Pos origin, Pos target)
{
	double dy, dx;
	int distance;
	dx = target.y - origin.y;
	dy = target.x - origin.x;
	distance = floor(sqrt((dx*dx)+(dy*dy)));

	return distance;
}

bool isInMap(int y, int x)
{
	if ((0<y&& y<MAP_HEIGHT-1) && (0<x && x<MAP_WIDTH-1))
		return true;
	return false;
}

bool lineOfSight(Tile** map, Pos origin, Pos target)
{
	int t, y, x, abs_delta_y, abs_delta_x, sign_y, sign_x, delta_x, delta_y;
	
	delta_y = origin.y - target.y;
	delta_x = origin.x - target.x;
	abs_delta_y = abs(delta_y);
	abs_delta_x = abs(delta_x);
	sign_y = getSign(delta_y);
	sign_x = getSign(delta_x);

	y = target.y;
	x = target.x;

	if (abs_delta_x > abs_delta_y)
	{
		t = abs_delta_y * 2 - abs_delta_x;

		do
		{
			if (t>=0)
			{
				y += sign_y;
				t -= abs_delta_x * 2;
			}

			x += sign_x;
			t += abs_delta_y * 2;

			if (y == origin.y && x == origin.x)
				return true;
		} while (CHK(map[y][x].attrFlags, TRANSPARENT));

		return false;
	}
	else
	{
		t = abs_delta_x * 2 - abs_delta_y;

		do
		{
			if (t>=0)
			{
				x += sign_x;
				t -= abs_delta_y * 2;
			}

			y += sign_y;
			t += abs_delta_x * 2;

			if (y == origin.y && x == origin.x)
				return true;
		} while (CHK(map[y][x].attrFlags, TRANSPARENT));

		return false;
	}
}

int getSign(int a)
{
	return (a >= 0) - (a < 0);
}