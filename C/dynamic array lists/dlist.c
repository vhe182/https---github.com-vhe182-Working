#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "dlist.h"

void debug_dlist(struct dlist *p)
{
  int i;

  fprintf(stderr,"\nDynamic List\n\n");
  fprintf(stderr,"   sz    = %d\n",p->sz);
  fprintf(stderr,"   maxsz = %d\n",p->maxsz);
  for( i = 0; i < p->maxsz; i++)
  {
      printf("%s", p->item[i]);
  }
}
void prt_dlist(struct dlist *p)
{
  int i;

  for( i = 0; i< p->sz; i++)
  {
    fprintf(stdout,"%s", p->item[i]);
  }
}
struct dlist *init_dlist(int num)
{
  struct dlist *p;

  p = malloc(DLISTSZ(num));
  if(p == NULL)
  {
    return NULL;
  }
  
  p->sz = 0;
  p->maxsz = num;
  
  return(p);
}

int ins_dlist(char *str, struct dlist **p)
{
  struct dlist *q;

  if ((*p)->sz == (*p)->maxsz)
  {
    q = realloc(*p, DLISTSZ((*p)->maxsz + INCRSZ));
    if( q == NULL)
    { 
      return(-1);
    }
    q->maxsz += INCRSZ;
    *p = q;
  }
  strcpy((*p)->item[(*p)->sz], str);
  (*p)->sz++;
  return(0);
}
