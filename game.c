#include "game.h"
#include "driver.h"
#include "pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define H 20
#define W 34
#define HMAX 1024
#define NStage 8
#define MaxLife 3
Game g;

static const char *level1[8] = {
  "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
  "JFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFJ"
  "JEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFJ"
  "JAAAAAABBBBAAAADAAAFFFFFFFFFFFFFFJ"
  "JFFFFFFFFFFFFFFDCCCCCCCCCHEEEEEHEJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFAAAAAAADJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JEEEEEEEFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JAAAAAADEECCCCCDEEHEEEEEEEEHEEEEDJ"
  "jAAAAAADAAFFFFFAAAAAAAAAAADAAAAADJ"
  "JFFFFFFDFFFFFFFCCCCCCCCCDFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JEEEHEEDCCCCCEEEEEEFFFFADHDEEEEEDJ"
  "JAAAAAADFFFFFAAAAADFFFFBBBBAAAAADJ"
  "JFFFFFFDFFFFFFFFFFDFFFFFFFFFFFFFDJ"
  "JEEEHEEDEEEEEEEEEEDEEEEEEHEEEEEEDJ"
  "JAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAJ"
  "JBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBJ",

  "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
  "JFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFJ"
  "JEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFJ"
  "JAAAAAABBBBAAAADAAAFFFFFFFFFFFFFFJ"
  "JCCCCCCCCCCCCCCDCCCCCCCCCHEEEEEHEJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFAAAAAAADJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JEEEEEEDEECCCCCDEEHEEEEEEEEHEEEEDJ"
  "jAAAAAADAAFFFFFAAAAAAAAAAADAAAAADJ"
  "JFFFFFFDFFFFFFFCCCCCCCCCDFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JEEEHEEDCCCCCEEEEEEFFFFADHDEEEEEDJ"
  "JAAAAAADFFFFFAAAAADFFFFBBBBAAAAADJ"
  "JFFFFFFDFFFFFFFFFFDFFFFFFFFFFFFFDJ"
  "JEEEHEEDEEEEEEEEEEDEEEEEEHEEEEEEDJ"
  "JAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAJ"
  "JBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBJ",

  "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
  "JFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFJ"
  "JEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFJ"
  "JAAAAAABBBBBBBBDFFFFFFFFFFFFFFFFFJ"
  "JFFFFFFFFFFFFFFDCCCCCCCCCHEEEEEHEJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFAAAAAAADJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JEEEEEEEFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JAAAAAADEECCCCCDEEHEEEEEEEEHEEEEDJ"
  "jAAAAAADAAFFFFFAAAAAAAAAAADAAAAADJ"
  "JFFFFFFDFFFFFFFCCCCCCCCCDFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JEEEHEEDCCCCCEEEEEEFFFFADHDEEEEEDJ"
  "JAAAAAADFFFFFAAAAAFFFFFBBBBAAAAADJ"
  "JFFFFFFDFFFFFFFFFFFFFFFFFFFFFFFFDJ"
  "JEEEHEEDEEEEEEEEEEEEEEEEEHEEEEEEDJ"
  "JAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAJ"
  "JBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBJ",

  "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
  "JFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFJ"
  "JEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFJ"
  "JAAAAAABBBBAAAADAAAFFFFFFFFFFFFFFJ"
  "JCCCCCCCCCCCCCCDCCCCCCCCCHEEEEEHEJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFAAAAAAADJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JEEEEEEDEECCCCCDEEHEEEEEEEEHEEEEDJ"
  "jAAAAAADAAFFFFFAAAAAAAAAAADAAAAADJ"
  "JFFFFFFDFFFFFFFCCCCCCCCCDFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JEEEHEEDCCCCCEEEEEEFFFFADHDEEEEEDJ"
  "JBBBBBBFFFFFFAAAAADFFFFBBBBAAAAADJ"
  "JFFFFFFFFFFFFFFFFFDFFFFFFFFFFFFFDJ"
  "JEEEHEEEEEEEEEEEEEDEEEEEEHEEEEEEDJ"
  "JAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAJ"
  "JBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBJ",

  "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
  "JFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFJ"
  "JEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFJ"
  "JAAAAAABBBBAAAADAAAFFFFFFFFFFFFFFJ"
  "JFFFFFFFFFFFFFFDCCCCCCCCCHEEEEEHEJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFAAAAAAADJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JEEEEEEEFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JAAAAAADEECCCCCDEEHEEEEEEEEHEEEEDJ"
  "jAAAAAADAAFFFFFAAAAAAAAAAADAAAAADJ"
  "JFFFFFFDFFFFFFFCCCCCCCCCDFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JEEEHEEDCCCCCEEEEEEFFFFADHDEEEEEDJ"
  "JAAAAAADFFFFFAAAAADFFFFBBBBAAAAADJ"
  "JFFFFFFDFFFFFFFFFFDFFFFFFFFFFFFFDJ"
  "JEEEHEEDEEEEEEEEEEDEEEEEEHEEEEEEDJ"
  "JAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAJ"
  "JBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBJ",

  "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
  "JFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFJ"
  "JEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFJ"
  "JAAAAAABBBBAAAADAAAFFFFFFFFFFFFFFJ"
  "JCCCCCCCCCCCCCCDCCCCCCCCCHEEEEEHEJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFAAAAAAADJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JEEEEEEDEECCCCCDEEHEEEEEEEEHEEEEDJ"
  "jAAAAAADAAFFFFFAAAAAAAAAAADAAAAADJ"
  "JFFFFFFDFFFFFFFCCCCCCCCCDFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JEEEHEEDCCCCCEEEEEEFFFFADHDEEEEEDJ"
  "JAAAAAADFFFFFAAAAADFFFFBBBBAAAAADJ"
  "JFFFFFFDFFFFFFFFFFDFFFFFFFFFFFFFDJ"
  "JEEEHEEDEEEEEEEEEEDEEEEEEHEEEEEEDJ"
  "JAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAJ"
  "JBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBJ",

  "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
  "JFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFJ"
  "JEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFJ"
  "JAAAAAABBBBAAAADAAAFFFFFFFFFFFFFFJ"
  "JFFFFFFFFFFFFFFDCCCCCCCCCHEEEEEHEJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFAAAAAAADJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JEEEEEEEFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JAAAAAADEECCCCCDEEHEEEEEEEEHEEEEDJ"
  "jAAAAAADAAFFFFFAAAAAAAAAAADAAAAADJ"
  "JFFFFFFDFFFFFFFCCCCCCCCCDFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JEEEHEEDCCCCCEEEEEEFFFFADHDEEEEEDJ"
  "JAAAAAADFFFFFAAAAADFFFFBBBBAAAAADJ"
  "JFFFFFFDFFFFFFFFFFDFFFFFFFFFFFFFDJ"
  "JEEEHEEDEEEHEEEEEEDEEHEEEHEEEEEEDJ"
  "JAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAJ"
  "JBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBJ",

  "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
  "JFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFJ"
  "JEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFJ"
  "JAAAAAABBBBAAAADAAAFFFFFFFFFFFFFFJ"
  "JCCCCCCCCCCCCCCDCCCCCCCCCHEEEEEHEJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFAAAAAAADJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFFDJ"
  "JEEEEEEDEECCCCCDEEHEEEEEEEEHEEEEDJ"
  "jAAAAAADAAFFFFFAAAAAAAAAAADAAAAADJ"
  "JFFFFFFDFFFFFFFCCCCCCCCCDFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JFFFFFFDFFFFFFFFFFFFFFFADFDFFFFFDJ"
  "JEEEHEEDCCCCCEEEEEEFFFFADHDEEEEEDJ"
  "JAAAAAADFFFFFAAAAADFFFFBBBBAAAAADJ"
  "JFFFFFFDFFFFFFFFFFDFFFFFFFFFFFFFDJ"
  "JEEEHEEDEEEEEEEEEEDEEEEEEHEEEEEEDJ"
  "JAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAJ"
  "JBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBJ"
};

static unsigned long long int turn=0;


static void automaticMove(int);
static void processMove(int);

static unsigned char bg[H * W];
static int start=0;
static int stage=0;
static int score=0;
static int scoreRequiredToWinStage=0;
static int enemyNumber=3;
static Entity entity[4];
static hole_t _fifo[HMAX];
static int fifoHead=0,fifoTail=0;
static int lodeLife=MaxLife;


static void (* pointerToMove)(int)=processMove; 

static int dirx[] = {0, -1, 1, 0, 0 };
static int diry[] = {0, 0, 0, -1, 1 };









/*---------------------------------------------------------------------------------------------------------*/


  
static void healTheEnemy(int ent_id){
  static int x=1;
  
  entity[ent_id].x=x;
  entity[ent_id].y=1;
  entity[ent_id].state=Healthy;
  
  x=(x + 10) % 15;
}
static void gameOver(){
  
  const char game_over[]={
    "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
    "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
    "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
    "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
    "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
    "JJJJJJBBBJJJBJJJBJJJBJBBBJJJJJJJJJ"
    "JJJJJJBJJJJBJBJJBBJBBJBJJJJJJJJJJJ"
    "JJJJJJBJJJBBBBBJBJBJBJBBBJJJJJJJJJ"
    "JJJJJJBJBJBJJJBJBJJJBJBJJJJJJJJJJJ"
    "JJJJJJBBBJBJJJBJBJJJBJBBBJJJJJJJJJ"
    "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
    "JJJJJJBBBJBJJJBJBBBJBBBJJJJJJJJJJJ"
    "JJJJJJBJBJBJJJBJBJJJBJJBJJJJJJJJJJ"
    "JJJJJJBJBJBJJJBJBBBJBBBJJJJJJJJJJJ"
    "JJJJJJBJBJJBJBJJBJJJBJBJJJJJJJJJJJ"
    "JJJJJJBBBJJJBJJJBBBJBJJBJJJJJJJJJJ"
    "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
    "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
    "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
    "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
  };
  for (int i=0; i < H*W; ++i)
    bg[i]=game_over[i]-'A';
  
  
}



static void reinitAllHoles(void){
  if ((scoreRequiredToWinStage > 0)){
      for (int i = fifoHead; i < fifoTail; ++i){
	bg[_fifo[i].y*W+_fifo[i].x]=Wall;
	_fifo[i].turn=106;
       
      }
    }
    else {
      fifoHead=0;
      fifoTail=0;
    }


}
  
static void resetGame(void){
  
  
  
  entity[Lode].x = H-1;
  entity[Lode].y = W-W/2;
  entity[Lode].state=Healthy;
  reinitAllHoles();
  for (int i=1; i <= enemyNumber ; i++){
  healTheEnemy(i);
  }
  start=0;
  turn=0;
 
}
       


static void listAHole(int y,int x){

  hole_t tmp;
  tmp.y=y;
  tmp.x=x;
  tmp.state=Empty;
  tmp.turn=0;
  bg[y*W+x]=HalfHole;
  if (!(fifoTail < HMAX))
    fifoTail=0;
   
    _fifo[fifoTail++]=tmp;
   
  
  
}
/*--------------------------------------------------------------------------------------------------------*/


static void fillTheHole(void){
  int b=fifoHead;
  
  
  if (!(fifoHead < HMAX))
    fifoHead = 0;
  for (int i=0; i<4; ++i){
    
    if (_fifo[b].y == entity[i].y && _fifo[b].x == entity[i].x){
      entity[i].state=Dead;
    
    }
  }
  bg[_fifo[b].y*W+_fifo[b].x]=Wall;
  _fifo[b].state=Empty;
  _fifo[b].turn=0;
  fifoHead++;
}


static void initStage (void){
  
  if (!(stage < NStage))return;

  reinitAllHoles();
  for(int i = 0; i < H * W; ++i){
    g.background[i] = level1[stage][i] - 'A';
    if (g.background[i] == Food)
      scoreRequiredToWinStage++;
  }
  
  scoreRequiredToWinStage+=enemyNumber;
  resetGame();
  for (int j=1;j<=enemyNumber;j++){
     
    entity[j].Neverdead=1;
      
 }
  lodeLife=MaxLife; 
}


/*-----------------------------------------------------------------------------------------------------------*/

static void checkAllHoles(void){
  
  
  
  for ( int i = fifoHead; i < fifoTail; ++i ){
    
    _fifo[i].turn++;
    if ( _fifo[i].turn  >= 5 && _fifo[i].turn < 100 ){
      bg[_fifo[i].y*W+_fifo[i].x]=Hole;
       
    }
    else if( (_fifo[i].turn > 0 && _fifo[i].turn  < 5) || (_fifo[i].turn >= 100 && _fifo[i].turn < 105) ){
      bg[_fifo[i].y*W+_fifo[i].x]=HalfHole;
      
    }
    else
      fillTheHole();
  }
    
    
}




/*---------------------------------------------------------------------------------------------------------*/





    
static void digHole(int dir){
  if (dir == Right){
    if ((bg[(entity[Lode].y+1) * W + (entity[Lode].x+1)] == Wall) && (bg[entity[Lode].y * W + entity[Lode].x+1] != Block && bg[entity[Lode].y * W + entity[Lode].x+1] != Wall)){
      listAHole(entity[Lode].y+1,entity[Lode].x+1);
    }
  }
  if (dir == Left){
    if ((bg[(entity[Lode].y+1) * W + (entity[Lode].x-1)] == Wall) && (bg[entity[Lode].y * W + entity[Lode].x-1] != Block && bg[entity[Lode].y * W + entity[Lode].x-1] != Wall)){
      listAHole(entity[Lode].y+1,entity[Lode].x-1);
    }
  }
  else return;
}

/*-------------------------------------------------------------------------------------------------------*/

static int * generateMaze(void){
  int *t=malloc(H*W*sizeof *t);
  for (int i=0;i<H; i++){
    for (int j=0; j<W; j++){
      if ( i == 0 || j==0 || j == W-1 || i == H-1)
	t[i*W+j]=-1;
      if ( bg[i*W+j] == Way || bg[i*W+j] == Ladder || bg[i*W+j] == Rope || bg[i*W+j] == Food)
	t[i*W+j]=0;
      else t[i*W+j]=-1;
    }
  }
  
  return t;



}

/*-----------------------plus court Way--------------------------------------------------------------------*/

void subShorterWay( int *t, int x1, int y1, int x2, int y2,int w, int v,int *s,int dir[4][2] ){
  
  v++;
  
  t[y1*w+x1]=v;
  
  if (x1 == x2 && y1 == y2){
    (*s)=1;
    
    return;
      
    
  }else{
    if (t[y1*w+x1] == -1)return ;
    else{
      for (int i=0; i<4; i++){
	if (v < t[(y1+dir[i][1])*w+x1+dir[i][0]] || t[(y1+dir[i][1])*w+x1+dir[i][0]] == 0){
	  subShorterWay(t,x1+dir[i][0],y1+dir[i][1],x2,y2,w,v,s,dir);
	}
      }
    }
  }
}

void shorterWay ( int *t, int x1, int y1, int x2, int y2,int w, int id) {
  int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
  int s=0;
  int g;
  tuple tmp;
  
  if (s == 0)
    subShorterWay(t,x1,y1,x2,y2,w,0,&s,dir);

  
  if (s == 1){
    
    g=t[y2*w+x2];
    while(g != 1){
      for (int i=0; i < 4; i++){
	if(t[(y2+dir[i][1])*w+x2+dir[i][0]] > -1){
	  if(t[(y2+dir[i][1])*w+x2+dir[i][0]]+1 == t[y2*w+x2]){
	    tmp.x=x2;
	    tmp.y=y2;
	    push(&tmp,id);
	    x2 += dir[i][0];
	    y2 += dir[i][1];
	    g=t[y2*w+x2];
	  }
	}
      }

      
    }

  }
  
    
}

/*-------------------------------------------------------------------------*/
static int distance(Entity e1,Entity e2){
  int r=abs(e2.x-e1.x)+abs(e2.y-e1.y);
  return r;

}






/*-----------------------------------------------------------------*/


static void moveEnemy ( int ent_id ){
  tuple coup_prochain;
   int *maze=generateMaze();
   if (entity[Lode].dir == Fall)return;
   if((bg[entity[ent_id].y * W + entity[ent_id].x] == Rope && entity[Lode].y > entity[ent_id].y) || (bg[(entity[ent_id].y) * W + entity[ent_id].x] == EmptyBg)){
    
    entity[ent_id].y++;
    entity[ent_id].dir=Fall;
	return;
  }
   if ((distance(entity[Lode],entity[ent_id]) == 0 || (distance(entity[Lode],entity[ent_id]) == 1 && entity[ent_id].state==Healthy)) && entity[Lode].y >= entity[ent_id].y || entity[Lode].state == Dead){
    resetGame();
    lodeLife--;
   }
  if (entity[ent_id].state == Healthy && entity[Lode].state == Healthy && bg[entity[Lode].y * W + entity[Lode].x] != EmptyBg){
    shorterWay(maze,entity[ent_id].x,entity[ent_id].y,entity[Lode].x,entity[Lode].y,W,ent_id);
 
    coup_prochain=*(struct tuple *)pop(ent_id);
    for (int i = 1; i < 5; ++i)
      if (dirx[i] == coup_prochain.x - entity[ent_id].x && diry[i] == coup_prochain.y - entity[ent_id].y){
	entity[ent_id].dir = i;
      }
    entity[ent_id].y=coup_prochain.y;
    entity[ent_id].x=coup_prochain.x;
    free(maze);
  }
  else if(entity[ent_id].state == Dead){
    score += 10;
    healTheEnemy(ent_id);
  }


  else return;
 
  
  
}


/*----------------------------------------------------------------------------------------------*/
static void moveAllEnemies(void){

  int i;
  for ( i = 1; i < 4; ++i){
    moveEnemy(i);
  }
}



/*-----------------------------------------------------------------------------------------------*/






static void processMove ( int move) {
  int moveDisplay=(move>0)?move:entity[Lode].dir;
  int nextx = entity[Lode].x + dirx[move];
  int nexty = entity[Lode].y + diry[move];
  
  if (move != Nothing){
    start=1;
   
  }
  
  if ( entity[Lode].state == Healthy || entity[Lode].state == InRisk ){
    
    if ( move == HoleLeft ){
      entity[Lode].dir = HoleLeft;
      digHole(Left);
      return;
    }
    if ( move == HoleRight ){
       entity[Lode].dir = HoleRight;
      digHole(Right);
      return;
    }
    if ( (bg[(entity[Lode].y-1) * W + entity[Lode].x] == EmptyBg && move==Up) || (entity[Lode].state == InRisk && move==Up) || (bg[(entity[Lode].y-1) * W +entity[Lode].x] == Hole && move==Up)){
      return;
    }
    if ( bg[entity[Lode].y * W + entity[Lode].x] == EmptyBg ){
      
      pointerToMove=automaticMove;
      return;
    }
    

    
    
  

    
  
    
    if (nextx <= 0 || nexty <= 0 || nextx >= W-1 || nexty >= H-1 || bg[nexty * W + nextx] == Wall || bg[nexty * W + nextx] == Block)
      return;
    entity[Lode].x = nextx;
    entity[Lode].y = nexty;
    entity[Lode].dir = moveDisplay;
  }
  
  else return;
  

  

  
}
  
static void automaticMove ( int move ){
   
  entity[Lode].y++;
  entity[Lode].dir=Fall;
  pointerToMove=processMove;
  return;
}



static void eatFood ( void ) {
  if ( bg[entity[0].y * W + entity[0].x] == Food ){
    bg[entity[0].y * W + entity[0].x]=(level1[stage][entity[0].y * W + entity[0].x]-'A' != Food)? level1[stage][entity[0].y * W + entity[0].x]-'A':Way;
    scoreRequiredToWinStage--;
  }
}
static void checkEntity(void){
  int j;
  
  
  for (j=1; j<enemyNumber; ++j){
    
      if (entity[j].state == InRisk){
	entity[j].nturn++;
      }
  }
  
}

static void getOutOfHole(void){
  int i;
  checkEntity();
  if (entity[Lode].state == InRisk && (bg[(entity[Lode].y+1) * W + entity[Lode].x] != Block && bg[(entity[Lode].y+1) * W + entity[Lode].x] != Wall) ){
    entity[Lode].state=Healthy;
    entity[Lode].y+=1;
    for (i=fifoHead; i<fifoTail; ++i)
      if (entity[Lode].y-1 == _fifo[i].y && entity[Lode].x == _fifo[i].x && _fifo[i].state == Full)
	_fifo[i].state = Empty;
  }
  for (i = 1; i < 4; ++i){
    if (entity[i].state == InRisk && entity[i].nturn >= 100/2){
      entity[i].dir=(entity[i].x > entity[Lode].x) ? Left:Right;
      entity[i].y-=1;
      entity[i].state=Healthy;
      for (int j=fifoHead; j<fifoTail; ++j)
	if (entity[i].y+1 == _fifo[j].y && entity[i].x == _fifo[j].x && _fifo[j].state == Full)
	  _fifo[j].state = Empty;
	  
	
    }
  }

}
  
  



static void fallInHole ( void ) {
  for (int i=0;i < 4; i++){
    //printf("y:%d,x:%d,bg %d\n",entity[i].y,entity[i].x,bg[(entity[i].y+1)*W+entity[i].x]);
    if (bg[(entity[i].y+1)*W+entity[i].x] == Hole){
      for (int j=fifoHead; j < fifoTail+1;j++){
	if ((entity[i].y+1 == _fifo[j].y) && (entity[i].x == _fifo[j].x) && (_fifo[j].state == Empty)){
	  
	  entity[i].y+=1;
	  
	  entity[i].state=InRisk;
	  entity[i].nturn=0;
	  entity[i].dir=inHole;
	  bg[(entity[i].y-1)*W+entity[i].x]=(i>0 && entity[i].Neverdead == 1)?Food:bg[(entity[i].y-1)*W+entity[i].x];
	  entity[i].Neverdead = 0;
	  _fifo[j].state=Full;
	}
      }
      
    }
  }
}
/*---------------------------------------------------------------------------------------------*/
static void positionInGame(int move){
   for (int i = 0; i < 4; ++i){
	
     entity[i].dir=(bg[entity[i].y * W + entity[i].x] == Rope)? ((entity[i].dir == Right)?inRopeRight:((entity[i].dir == Left)?inRopeLeft:entity[i].dir)):entity[i].dir;
   



   }
	


} 

/*---------------------------------------------------------------------------------------------*/
static void callback(void* d) {
  const Driver* dr = (Driver*)d;
  if (!(lodeLife > 0)){
    gameOver();
   
  }
  if (scoreRequiredToWinStage==0){
    stage++;
    initStage();
  }
 
  int move = dr->get_move();
  turn++; 
  
  pointerToMove(move);
  
  eatFood();
  checkAllHoles();
 
  if (start != 0 && turn % 2 == 0){
    moveAllEnemies();
  }
  
  
  
  
  fallInHole();
  getOutOfHole();
  positionInGame(move);
  dr->draw_bg();
  for (int i=0; i < 4 && lodeLife > 0; ++i)
    dr->draw_entity(i);
 
  dr->update();
    
  
}



void init_game(const Driver* dr) {
  int i,j,y,x;
  initialState();
  g.h = H;
  g.w = W;
  
  g.background = bg;
  g.entity = entity;
  for(int i = 0; i < H * W; ++i)
    g.background[i] = level1[stage][i] - 'A';

 
  for (int j=1;j<=enemyNumber;j++)
    entity[j].Neverdead=1;
  
  for (int j=1;j<=enemyNumber;j++)
    pileInit(sizeof(tuple),j);
  
  
  
  
  dr->init(&g);
  dr->start(callback);
}

