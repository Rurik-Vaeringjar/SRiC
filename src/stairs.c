#include <rogue.h>

Ob* createStairs(Pos pos, char ch)
{
	Ob* newOb = calloc(1, sizeof(Ob));
	
	newOb->entity = calloc(1, sizeof(Entity));
	newOb->entity->ch = ch;
	newOb->entity->color = COLOR_PAIR(VISIBLE_COLOR);
	newOb->entity->pos.y = pos.y;
	newOb->entity->pos.x = pos.x;
	newOb->flags = 0b000000000;
	SET(newOb->flags, STAIRS | (ch=='>' ? NEXT : 0));

	return newOb;
}

void useStairs(Floor* floor)
{
	if (CHK(floor->map[player->pos.y][player->pos.x].obFlags, STAIRS))
	{
		clearFOV(floor->map, player);
		if(CHK(floor->map[player->pos.y][player->pos.x].obFlags, NEXT))
		{
			nextFloor();
			player->pos.y = floors[curFloor]->start_pos.y;
			player->pos.x = floors[curFloor]->start_pos.x;
		}
		else
		{
			prevFloor();
			player->pos.y = floors[curFloor]->end_pos.y;
			player->pos.x = floors[curFloor]->end_pos.x;
		}
		makeFOV(floors[curFloor]->map, player);
	}
}