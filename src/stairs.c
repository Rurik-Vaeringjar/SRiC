#include <rogue.h>

Ob* createStairs(Pos pos, char ch)
{
	Ob* newOb = calloc(1, sizeof(Ob));
	
	newOb->entity = calloc(1, sizeof(Entity));
	newOb->entity->ch = ch;
	newOb->entity->color = COLOR_PAIR(VISIBLE_COLOR);
	newOb->entity->pos.y = pos.y;
	newOb->entity->pos.x = pos.x;
	SET(newOb->flags, STAIRS);

	return newOb;
}

void useStairs(Floor* floor)
{
	if (CHK(floor->map[player->pos.y][player->pos.x].obFlags, STAIRS))
	{
		clearFOV(floor->map, player);
		if(floor->end_pos.y == player->pos.y &&
		   floor->end_pos.x == player->pos.x)
		{
			nextFloor();
			player->pos.y = floors[curFloor]->start_pos.y;
			player->pos.x = floors[curFloor]->start_pos.x;
		}
		else if (floor->start_pos.y == player->pos.y &&
				 floor->start_pos.x == player->pos.x &&
				 curFloor > 0)
		{
			prevFloor();
			player->pos.y = floors[curFloor]->end_pos.y;
			player->pos.x = floors[curFloor]->end_pos.x;
		}
		makeFOV(floors[curFloor]->map, player);
	}
	/*
	clearFOV(floor->map, player);
	if (floor->obList[0]->entity->pos.y == player->pos.y && 
		floor->obList[0]->entity->pos.x == player->pos.x)
	{
		nextFloor();
		player->pos.y = floors[curFloor]->start_pos.y;
		player->pos.x = floors[curFloor]->start_pos.x;
	}
	else if (floor->obList[1]->entity->pos.y == player->pos.y && 
			 floor->obList[1]->entity->pos.x == player->pos.x &&
			 curFloor > 0)
	{
		prevFloor();
		player->pos.y = floors[curFloor]->end_pos.y;
		player->pos.x = floors[curFloor]->end_pos.x;
	}
	makeFOV(floors[curFloor]->map, player);*/
}