#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sstor.h"

struct dlist *init_dlist(void)
{
  struct dlist *p;

  p = malloc(DLISTSZ(INITSZ));
  if( p == NULL)
    return NULL;
  p->sz = 0;
  p->maxsz = INITSZ;
  return (p);
}
int ins_dlist(char *str, struct dlist **p)
{
  struct dlist *x;
  if( (*p)->sz + strlen(str) + 1 > (*p)->maxsz)
  {
    x = realloc(*p, DLISTSZ((*p)->maxsz + strlen(str) + 1 + INCRSZ));
    if(x == NULL)
      return (-1);

    x->maxsz += strlen(str) + 1 + INCRSZ;
    *p = x;
  }
  
  while(*str != '\0')
  {
    (*p)->line[(*p)->sz] = *str;
    (*p)->sz++;
    str++;
  }
  (*p)->line[(*p)->sz++] = '\0';
  return(0);
}
void prt_dlist(struct dlist *p)
{
  int i;
  
  for( i = 0; i < p->sz; i++)
    fprintf(stdout,"%d___%c\n", i, p->line[i]);
}
