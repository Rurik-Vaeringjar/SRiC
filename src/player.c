#include <rogue.h>

Player* createPlayer(Pos start_pos)
{
	Player* newPlayer = calloc(1, sizeof(Player));

	Entity* entity = calloc(1, sizeof(Entity));
	entity->pos.y = start_pos.y;
	entity->pos.x = start_pos.x;
	entity->ch = '@';
	entity->color = COLOR_PAIR(VISIBLE_COLOR);
	newPlayer->entity = entity;
	
	newPlayer->stats.hp = 50;
	newPlayer->stats.MAX_HP = 50;
	newPlayer->stats.armor = 0;
	newPlayer->stats.dmg = 5;
	
	return newPlayer;
}

void handleInput(int input)
{
	bool move = true;
	Pos newPos = {player->entity->pos.y, player->entity->pos.x};

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
			clearFOV(floor->map, player->entity);
			floor->map[player->entity->pos.y][player->entity->pos.x].occupied = -1;
			player->entity->pos.y = newPos.y;
			player->entity->pos.x = newPos.x;
			floor->map[newPos.y][newPos.x].occupied = -2;
			makeFOV(floor->map, player->entity);
		}
	}
}

