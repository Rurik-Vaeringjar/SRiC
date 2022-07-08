#include <rogue.h>

char attack(Stats* attacker, Stats* defender)
{
	int dealt = attacker->dmg - defender->armor;
	defender->hp -= dealt;
	if (defender->hp <= 0)
		return 1;
	return 0;
}