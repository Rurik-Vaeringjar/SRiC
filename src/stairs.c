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
	if (CHK(floor->map[player->entity->pos.y][player->entity->pos.x].obFlags, STAIRS))
	{
		clearFOV(floor->map, player->entity);
		if(CHK(floor->map[player->entity->pos.y][player->entity->pos.x].obFlags, NEXT))
		{
			nextFloor();
			player->entity->pos.y = floors[curFloor]->start_pos.y;
			player->entity->pos.x = floors[curFloor]->start_pos.x;
		}
		else
		{
			prevFloor();
			player->entity->pos.y = floors[curFloor]->end_pos.y;
			player->entity->pos.x = floors[curFloor]->end_pos.x;
		}
		makeFOV(floors[curFloor]->map, player->entity);
	}
}