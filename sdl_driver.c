#include "game.h"
#include "driver.h"
#include <time.h>
#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <unistd.h>
#include <SDL.h>
#include <SDL_image.h>

static int init(const Game* game);
static void start(void(*callback)(void*));
static int get_move(void);
static void draw_bg(void);
static void draw_entity(int ent_id);
static void update(void);

Driver sdl_driver = {
    .game = NULL,
    .init = init,
    .start = start,
    .get_move = get_move,
    .draw_bg = draw_bg,
    .draw_entity = draw_entity,
    .update = update
};

#define GAME (sdl_driver.game)

static SDL_Window *win;
static SDL_Renderer *ren;
static SDL_Texture* tiles[NCell];
static const char* tiles_files[] = { "files/mur.png", "files/roche.png", "files/corde.png","files/echelle.png","files/chemin.png","files/vide.png","files/demitrous.png","files/noriture.png","files/vide.png","files/vide.png"};
static SDL_Texture* sprites[NSprite];
static const char* sprites_files[] = { "files/lode_runner.png","files/red_head.png","files/red_head.png","files/red_head.png" };

enum { SZ = 32 };
enum { FPS = 0 };

static int load_sprites(void) {
    int i;
    SDL_Surface *png;
    
    for(i = 0; i < NSprite ; i++) {
      
        png = IMG_Load(sprites_files[i]);
        if (png == NULL){
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            printf("Error: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }
        sprites[i] = SDL_CreateTextureFromSurface(ren, png);
        SDL_FreeSurface(png);
    }
    return 0;
}

static int load_tiles(void){
    int i;
    SDL_Surface *png;
    for(i = 0; i < NCell; ++i) {
      png = IMG_Load(tiles_files[i]);
        if (png == NULL){
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            printf("Error: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }
        tiles[i] = SDL_CreateTextureFromSurface(ren, png);
        SDL_FreeSurface(png);
    }
    return 0;
}

static int init(const Game* game) {
    int i;

    GAME = game;
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL_Init Error: %s\n",  SDL_GetError());
        return 1;
    }
    
    win = SDL_CreateWindow("Lode Runner", 0, 0, (GAME->w) * SZ, (GAME->h) * SZ, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
  
    if(load_tiles())
        return 1;
  
    if(load_sprites())
        return 1;
  
    return 0;
}

static void start(void(*callback)(void*)) {
  clock_t t2,t1;
  float t;
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(callback, &sdl_driver, FPS, 0);
#else
    for(;;) {
      t1=clock();
      callback(&sdl_driver);
      t2=clock();
      t=(float)t2-t1;
      usleep(100000-t);
    }
#endif
}



static int get_move(void){
  SDL_PumpEvents();
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_P]){
    SDL_Quit();
    exit(0);
  }
  if (state[SDL_SCANCODE_W]){
    return Up;
  }
  if (state[SDL_SCANCODE_S]){
    return Down;
  }
  if (state[SDL_SCANCODE_D]){
    return Right;
  }
  if (state[SDL_SCANCODE_A]){
    return Left;
  }
  if (state[SDL_SCANCODE_Q]){
    return HoleLeft;
  }
  if (state[SDL_SCANCODE_E]){
    
    return HoleRight;
  }
  else return Nothing;
}

static void draw_bg(void) {
    SDL_RenderClear(ren);
    int y, x;
    SDL_Rect dst = {.x = 0, .y = 0, .w = SZ, .h = SZ };
    for(y = 0; y < GAME->h; ++y) {
        for(x = 0; x < GAME->w; ++x) {
            dst.x = x * SZ;
            dst.y = y * SZ;
            int typecell = GAME->background[y * GAME->w + x];
            SDL_RenderCopy(ren, tiles[typecell], NULL, &dst);
        }
    }
}

static void draw_entity(int ent_id) {
  int tab_dirs[11][2]={{1,0},{3,3},{3,0},{2,6},{2,6},{1,16},{1,15},{1,17},{3,9},{3,9},{1,8}};//l'indice des lignes represente les differente direction de l'entité puis l'indice de la colonne 0 c'est le nombre de photo ou image a afficher et l'indice 1 c'est le décalage dans l'image.
  
  static int sp[4];//pour chaque entité y'a une variable sp spéciale à elle.
  
  SDL_Rect src = {.x = 0, .y = 0, .w = SZ, .h = SZ };
  SDL_Rect dst = {.x = SZ * GAME->entity[ent_id].x, .y = SZ * GAME->entity[ent_id].y, .w = SZ, .h = SZ };
  src.x = sp[ent_id] * 32;
  SDL_RenderCopy(ren, sprites[ent_id], &src, &dst);
  sp[ent_id]=((sp[ent_id] + 1)%tab_dirs[GAME->entity[ent_id].dir][0])+tab_dirs[GAME->entity[ent_id].dir][1];
  
}

static void update(void) {
 SDL_RenderPresent(ren);
}

