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

void handleInput(char input)
{
	Pos newPos = {player->pos.y, player->pos.x};

	switch(input)
	{
		//move up
		case 'w':
			//player->pos.y--;
			newPos.y--;
			break;
		//move down
		case 's':
			//player->pos.y++;
			newPos.y++;
			break;
		//move left
		case 'a':
			//player->pos.x--;
			newPos.x--;
			break;
		//move right
		case 'd':
			//player->pos.x++;
			newPos.x++;
			break;
		case 'k':
			killMob(mobList[rand()%numMobs]);
			//reduceMobList(rand()%numMobs);
			break;
		default:
			break;
	}

	movePlayer(newPos);
}

int mobCollision(Pos target)
{
	for (int i=0; i<numMobs; i++)
		if (target.y == mobList[i]->entity->pos.y && target.x == mobList[i]->entity->pos.x)
			return i;
	return -1;
}

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
			map[newPos.y][newPos.x].occupied = 127;
			player->pos.y = newPos.y;
			player->pos.x = newPos.x;
			makeFOV(player);
		}
	}
}

