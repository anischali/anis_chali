
#include "pile.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

static size_t _elsize[10], _nel[10];
static unsigned char *_pile[10];
static int _haut[10];


extern void initialState(void){
  for (int i=0; i < 10; ++i){
    _elsize[i]=0;
    _nel[i]=0;
    _haut[i]=-1;
    _pile[i]=NULL;
  }
}

extern void pileInit(size_t s,int n){
  _elsize[n]=s;
  if (_pile[n]){
    free(_pile[n]);
  }
  
  _pile[n]=malloc(_elsize[n] * (_nel[n] = 1024) * sizeof *_pile[n]);
  assert(_pile[n]);
  _haut[n];
}



extern int vide(int n){
  return _haut[n] < 0;
}



extern void * pop(int n){
  return (void *)&_pile[n][_elsize[n] * _haut[n]--];
}


extern void push(void * data,int n){

  if (++_haut[n] == _nel[n]){
    _pile[n]=realloc(_pile[n], (_nel[n] *= 2) * _elsize[n] * sizeof *_pile[n]);
    assert(_pile[n]);
  }
  memcpy(&_pile[n][_elsize[n]*_haut[n]],data,_elsize[n]);
}



extern void quitPile(void){
  for (int i=0; i < 10; i++)
    if (_pile[i])
      free(_pile[i]);
   
  
}
