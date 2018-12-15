typedef struct Game Game;
typedef struct Driver Driver;
typedef struct Entity Entity;
typedef struct hole_t hole_t;
typedef struct tuple tuple;


struct tuple{
  int x,y;
};

struct Entity {
  int x;
  int y;
  int id;
  int dir;
  int state;
  int nturn;
  int Neverdead;
};

struct Game {
  int h;
  int w;
  unsigned char* background;
  Entity* entity;
};

struct hole_t{
  int x;
  int y;
  int turn;
  int state;
};
enum{
  InRisk,
  Healthy,
  Dead
};

enum {
  Empty,
  Full
};
enum {
  Wall,
  Block,
  Rope,
  Ladder,
  Way,
  EmptyBg,
  HalfHole,
  Food,
  Hole,
  Limits,
  NCell
    
};


enum {
  Lode,
  Enemy1,
  Enemy2,
  Enemy3,
  NSprite
  
};

enum {
  Nothing, Left, Right, Up, Down, HoleLeft,HoleRight, Fall, inRopeLeft,inRopeRight ,inHole 
};

void init_game(const Driver*);


