#include <rogue.h>

Entity* createPlayer(Pos start_pos)
{
	Entity* newPlayer = calloc(1, sizeof(Entity));

	newPlayer->pos.y = start_pos.y;
	newPlayer->pos.x = start_pos.x;
	newPlayer->ch = '@';
	newPlayer->color = COLOR_PAIR(VISIBLE_COLOR);

	return newPlayer;
}

void handleInput(int input)
{
	bool move = true;
	Pos newPos = {player->pos.y, player->pos.x};
	

	switch(input)
	{
		//move up
		case 'W':
		case 'w':
			newPos.y--;
			break;
		//move down
		case 'X':
		case 'x':
			newPos.y++;
			break;
		//move left
		case 'A':
		case 'a':
			newPos.x--;
			break;
		//move right
		case 'D':
		case 'd':
			newPos.x++;
			break;
		//move up+left
		case 'Q':
		case 'q':
			newPos.y--;
			newPos.x--;
			break;
		//move up+right
		case 'E':
		case 'e':
			newPos.y--;
			newPos.x++;
			break;
		//move down+right
		case 'C':
		case 'c':
			newPos.y++;
			newPos.x++;
			break;
		//move down+left
		case 'Z':
		case 'z':
			newPos.y++;
			newPos.x--;
			break;
		//wait
		case 'S':
		case 's':
			move = false;
			break;
		case 'l':
			move = false;
			useStairs(floors[curFloor]);
			break;
		case 'k':
			
			//killMob(mobList[rand()%numMobs]);
			//reduceMobList(rand()%numMobs);
			break;
		default:
			break;
	}

	if (move)
		movePlayer(floors[curFloor], newPos);
}


/*int mobCollision(Pos target)
{
	for (int i=0; i<numMobs; i++)
		if (target.y == mobList[i]->entity->pos.y && target.x == mobList[i]->entity->pos.x)
			return i;
	return -1;
}*/

void movePlayer(Floor* floor, Pos newPos)
{
	if (CHK(floor->map[newPos.y][newPos.x].attrFlags, WALKABLE))
	{
		char collision = floor->map[newPos.y][newPos.x].occupied;
		if (collision > -1)
		{	
			killMob(floor->map, floor->mobList[collision]);
			objectifyMob(collision);
		}
		else
		{
			clearFOV(floor->map, player);
			floor->map[player->pos.y][player->pos.x].occupied = -1;
			player->pos.y = newPos.y;
			player->pos.x = newPos.x;
			floor->map[newPos.y][newPos.x].occupied = -2;
			makeFOV(floor->map, player);
		}
	}
}

