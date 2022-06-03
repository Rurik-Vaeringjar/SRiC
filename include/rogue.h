#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>


//color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2
#define MOB_COLOR 3
#define SLIME_COLOR 4
#define CORPSE_COLOR 5
#define DEAD_SLIME_COLOR 6

//game states
#define PLAYER_TURN 0
#define MOB_TURN 1

//attribute flags
#define WALKABLE    (1 << 0) // 1
#define TRANSPARENT (1 << 1) // 2
#define VISIBLE     (1 << 2) // 4
#define SEEN        (1 << 3) // 8
 
//object flags
#define STAIRS (1 << 0) // 1
#define NEXT   (1 << 1) // 2
#define CORPSE (1 << 7) // 128

//flag macros
#define SET(n, f) ((n) |= (f))
#define CLR(n, f) ((n) &= ~(f))
#define TGL(n, f) ((n) ^= (f))
#define CHK(n, f) ((n) & (f))

typedef struct
{
	int y;
	int x;
} Pos;

typedef struct
{
	int color;			//AAAA
	char ch;			//B
	uint8_t attrFlags;	//C
	char occupied;		//D
	uint8_t obFlags;	//E
	// AAAA|BCDE
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
	Pos pos;			//AAAA|AAAA?
	int color;			//BBBB
	char ch;			//C
} Entity;

typedef struct
{
	int hp;
	int MAX_HP;

	unsigned char armor;

	unsigned char dmg;
} Stats;

typedef struct
{
	Stats stats;
	Entity* entity;
} Player;

typedef struct Mob
{
	Stats stats;
	Entity* entity;	
	char index;		
	uint8_t flags;
} Mob;

typedef struct Ob
{
	Entity* entity;
	char index;
	uint8_t flags;
} Ob;

typedef struct
{
	Mob** mobList;
	Ob** obList;
	Tile** map;

	char numObs;
	char sizeObs;
	char numMobs;
	char sizeMobs;

	Pos start_pos;
	Pos end_pos;	
} Floor;

//draw.c function prototypes
void drawMap(Tile** map);
void drawEntity(Entity* entity, bool visible);
void drawObs(Floor* floor);
void drawMobs(Floor* floor);
void drawUI(void);
void drawAll(void);

//engine.c function prototypes
bool cursesSetup(void);
void gameLoop(void);
void closeGame(void);

//map.c function prototypes
Tile** createMapTiles(void);
Pos* setupMap(Floor* floor);
void freeMap(Tile** map);

//room.c function prototypes
Room createRoom(int y, int x, int height, int width);
void addRoom(Floor* floor, Room room);
void connectRoomsCenter(Tile** map, Pos cntrA, Pos cntrB);

//fov.c function prototypes
void makeFOV(Tile** map, Entity* player);
void clearFOV(Tile** map, Entity* player);
int getDistance(Pos origin, Pos target);
bool isInMap(int y, int x);
bool lineOfSight(Tile** map, Pos origin, Pos target);
int getSign(int a);

//player.c function protoypes
Player* createPlayer(Pos start_pos);
void handleInput(int input);
void movePlayer(Floor* floor, Pos newPos);

//mob.c function prototypes
void killMob(Tile** map, Mob* mob);
void moveMob(Tile** map, Mob* mob);
void mobsTurn(void);

//mobs.c function prototypes
Mob* createMob(Pos spawn_pos, Stats base_stats, char ch);
void spawnMob(Floor* floor, Pos spawn_pos);
void initMobList(Floor* floor);
void appendMobList(Floor* floor, Mob* newMob);
void resizeMobList(Floor* floor, char mod);
void freeMob(Mob* mob);
void reduceMobList(Floor* floor, char index);
void freeMobList(Floor* floor);

//obs.c function prototypes
void objectifyMob(char index);
void initObList(Floor* floor);
void appendObList(Floor* floor, Ob* newOb);
void resizeObList(Floor* floor, char mod);
void freeOb(Ob* ob);
void reduceObList(Floor* floor, char index);
void freeObList(Floor* floor);

//floors.c function prototypes
void initFloors(void);
Floor* createFloor(void);
void newFloor(void);
void nextFloor(void);
void prevFloor(void);
void freeFloors(void);

//floor.c function prototypes
void initFloors(void);
void addFloor(Floor* floor);
Floor* createFloor(void);
void newFloor(void);
void saveFloor(void);
void loadFloor(unsigned char index);
void freeFloors(void);

//stairs.c
Ob* createStairs(Pos pos, char ch);
void useStairs(Floor* floor);

//externs
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern unsigned char numFloors;
extern unsigned char curFloor;
extern char numMobs;
extern char numObs;
extern Player* player;
extern Floor** floors;


#endif
