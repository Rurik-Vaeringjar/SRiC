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
	char occupied;
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
} Entity;

typedef struct Mob
{
	Entity* entity;
	char index;
} Mob;

typedef struct Ob
{
	Entity* entity;
	char index;
} Ob;

typedef struct
{
	Mob** mobList;
	unsigned char* numMobs;
	unsigned char* sizeMobs;

	Ob** obList;
	unsigned char* numObs;
	unsigned char* sizeObs;

	Tile** map;
	Pos start_pos;
	Pos end_pos;
} Floor;

//draw.c function prototypes
void drawMap(Tile** map);
void drawEntity(Entity* entity);
void drawObs(void);
void drawMobs(void);
void drawAll(void);

//engine.c function prototypes
bool cursesSetup(void);
void gameLoop(void);
void closeGame(void);

//map.c function prototypes
Tile** createMapTiles(void);
Pos* setupMap(Tile** map);
void freeMap(Tile** map);

//room.c function prototypes
Room createRoom(int y, int x, int height, int width);
void addRoom(Tile** map, Room room);
void connectRoomsCenter(Tile** map, Pos cntrA, Pos cntrB);

//fov.c function prototypes
void makeFOV(Tile** map, Entity* player);
void clearFOV(Tile** map, Entity* player);
int getDistance(Pos origin, Pos target);
bool isInMap(int y, int x);
bool lineOfSight(Tile** map, Pos origin, Pos target);
int getSign(int a);

//player.c function protoypes
Entity* createPlayer(Pos start_pos);
void handleInput(int input);
void movePlayer(Tile** map, Pos newPos);

//mob.c function prototypes
void killMob(Tile** map, Mob* mob);
void moveMob(Tile** map, Mob* mob);
void mobsTurn(void);

//mobs.c function prototypes
Mob* createMob(Pos spawn_pos, char ch);
void spawnMob(Pos spawn_pos);
void appendMobList(Mob* newMob);
void freeMob(Mob* mob);
void reduceMobList(Tile** map, char index);
void clearMobList(void);

//obs.c function prototypes
void objectifyMob(char index);
void appendObList(Ob* newOb);
void freeOb(Ob* ob);
void reduceObList(char index);
void clearObList(void);

//floors.c function prototypes
void initFloors(void);
Floor* createFloor(void);
void newFloor(void);
void nextFloor(void);
void prevFloor(void);
void freeFloors(void);


//externs
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern unsigned char numFloors;
extern unsigned char curFloor;
extern char numMobs;
extern char numObs;
extern Entity* player;
extern Mob** mobList;
extern Ob** obList;
extern Floor** floors;


#endif
