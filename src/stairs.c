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
	if (floor->obList[0]->entity->pos.y == player->pos.y && 
		floor->obList[0]->entity->pos.x == player->pos.x)
		nextFloor();
	else if (floor->obList[1]->entity->pos.y == player->pos.y && 
			 floor->obList[1]->entity->pos.x == player->pos.x &&
			 curFloor > 0)
		prevFloor();
}