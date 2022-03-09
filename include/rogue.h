#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2
#define MOB_COLOR 3
#define CORPSE_COLOR 4

//game states
#define PLAYER_TURN 0
#define MOB_TURN 1

typedef struct
{
	int y;
	int x;
} Pos;

typedef struct
{
	char ch;
	int color;
	bool walkable;
	bool transparent;
	bool visible;
	bool seen;
	bool occupied;
} Tile;

typedef struct
{
	int height;
	int width;
	Pos pos;
	Pos cntr;
} Room;

typedef struct
{
	Pos pos;
	char ch;
	int color;
	bool alive;
} Entity;

//draw.c function prototypes
void drawMap(void);
void drawEntity(Entity* entity);
void drawMobs(void);
void drawAll(void);

//engine.c function prototypes
bool cursesSetup(void);
void gameLoop(void);
void closeGame(void);

//map.c function prototypes
Tile** createMapTiles(void);
Pos setupMap(void);
void freeMap(void);

//room.c function prototypes
Room createRoom(int y, int x, int height, int width);
void addRoom(Room room);
void connectRoomsCenter(Pos cntrA, Pos cntrB);

//fov.c function prototypes
void makeFOV(Entity* player);
void clearFOV(Entity* player);
int getDistance(Pos origin, Pos target);
bool isInMap(int y, int x);
bool lineOfSight(Pos origin, Pos target);
int getSign(int a);

//player.c function protoypes
Entity* createPlayer(Pos start_pos);
void handleInput(int input);
void movePlayer(Pos newPos);

//mob.c function prototypes
void killMob(Entity* mob);
void moveMob(Entity* mob);

//mobs.c function prototypes
Entity* createMob(Pos spawn_pos, char ch);
void appendMobList(Entity* newMob);
void reduceMobList(int index);
void clearMobList(void);

//externs
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern int numMobs;
extern Entity* player;
extern Entity** mobList;
extern Tile** map;


#endif
