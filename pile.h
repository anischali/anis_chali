
#include <stdlib.h>
#ifndef _PILE_H
#define _PILE_H
#ifdef __cplusplus
extern "C" {
#endif
  extern void initialState(void);
  extern void pileInit(size_t,int );  
  extern void push(void *,int);
  extern void * pop(int);
  extern int vide(int);
  extern void quitPile(void);
#ifdef __cplusplus
}
#endif
#endif
