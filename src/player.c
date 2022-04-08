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
			break;
		//nextfloor
		case 'l':
			floors[currentFloor]->exit.y = player->pos.y;
			floors[currentFloor]->exit.x = player->pos.x;
			clearFOV(player);
			saveFloor();
			if(currentFloor == numFloors-1)
				newFloor();
			else
			{
				currentFloor++;
				loadFloor(currentFloor);
				player->pos.y = floors[currentFloor]->entry.y;
				player->pos.x = floors[currentFloor]->entry.x;
				makeFOV(player);
			}
			newPos.y = player->pos.y;
			newPos.x = player->pos.x;
			break;
		//previous floor
		case 'k':
			if(currentFloor != 0)
			{
				clearFOV(player);
				saveFloor();
				currentFloor--;
				loadFloor(currentFloor);
				player->pos.y = floors[currentFloor]->exit.y;
				player->pos.x = floors[currentFloor]->exit.x;
				makeFOV(player);
			}
			newPos.y = player->pos.y;
			newPos.x = player->pos.x;
			break;
		default:
			break;
	}

	movePlayer(newPos);
}


/*int mobCollision(Pos target)
{
	for (int i=0; i<numMobs; i++)
		if (target.y == mobList[i]->entity->pos.y && target.x == mobList[i]->entity->pos.x)
			return i;
	return -1;
}*/

void movePlayer(Pos newPos)
{
	if (map[newPos.y][newPos.x].walkable)
	{
		char collision = map[newPos.y][newPos.x].occupied;
		if (collision > -1)
		{	
			killMob(mobList[collision]);
			objectifyMob(collision);
		}
		else
		{
			clearFOV(player);
			map[player->pos.y][player->pos.x].occupied = -1;
			player->pos.y = newPos.y;
			player->pos.x = newPos.x;
			map[newPos.y][newPos.x].occupied = -2;
			makeFOV(player);
		}
	}
}

