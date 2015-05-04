#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "heap.h"


/***********DYNAMIC*LIST*FUNCTIONS*************/
void debug_heap(struct heap *p)
{
  int i;

  fprintf(stderr,"\nDynamic List\n\n");
  fprintf(stderr,"   sz    = %d\n",p->sz);
  fprintf(stderr,"   maxsz = %d\n",p->maxsz);
  for( i = 0; i < p->maxsz; i++)
  {
      printf("%d_____%d\n",i, p->item[i]);
  }
}
void print_heap(struct heap *p)
{
  int i;
  
  fprintf(stdout,"Current List\n");
  for( i = 0; i< p->sz; i++)
  {
    fprintf(stdout,"%d-", p->item[i]);
  }
  fprintf(stdout,"\n");
}
struct heap *init_heap(int num)
{
  struct heap *p;

  if((p = malloc(HLISTSZ(num))) == NULL)
  {
    return NULL;
  }
  
  p->sz = 0;
  p->maxsz = num;
  
  return (p);
}

int insert_heap(int num, struct heap **p)
{
  struct heap *q;

  if ((*p)->sz == (*p)->maxsz)
  {
    q = realloc(*p, HLISTSZ((*p)->maxsz + INCRHSZ));
    if( q == NULL)
    {
      return(-1);
    }
    q->maxsz += INCRHSZ;
    *p = q;
  }
  (*p)->item[(*p)->sz++] = num;
  siftup(*p,(*p)->sz -1);
  return(0);
}
/*********HEAP*FUNCTIONS***********************/
void build_heap(struct heap *p)
{
  int r;
  for( r = (p->sz)/2-1; r >= 0; r--)
    siftdown(p,r);
}
void siftdown(struct heap *p, int r)
{
  int val, left, right, sz;
  sz = p->sz;
  left = LEFT(r,sz);
  right = RIGHT(r,sz);
  val = p->item[r];
  
  while( (left != -1 && val > p->item[left]) ||
         (right != -1 && val > p->item[right]) )
  {
    if(right == -1 || p->item[left] <= p->item[right])
    {
      p->item[r] = p->item[left];
      p->item[left] = val;
      //printf("%d up, %d down\n", p->item[r], p->item[left]);
      r = left;
    }else{
      p->item[r] = p->item[right];
      p->item[right] = val;
      //printf("%d up, %d down\n", p->item[r], p->item[right]); 
      r = right; 
    }
    left = LEFT(r,sz);
    right = RIGHT(r,sz);
    //printf("r = %d\n", r);
  }
}
void siftup(struct heap *p, int r)
{
  int par, val;
  par = PARENT(r,p->sz);
  while( par != -1 && p->item[par] > p->item[r])
  {
    val = p->item[par];
    p->item[par] = p->item[r];
    p->item[r] = val;
    //printf("%d up, %d down\n", p->item[par], p->item[r]);
    r = par;
    par = PARENT(r, p->sz);
  }
}
int valid_heap(struct heap *p)
{       
  int r, left, right;

  for( r = 0; r <= (p->sz)/2-1 ; r++)
  {
    left = LEFT(r,p->sz);
    right = RIGHT(r,p->sz);
    if(left != -1 && p->item[r] > p->item[left])
      return(0);
    if(right != -1 && p->item[r] > p->item[right])
      return(0);
  }
  return(1);
}
int rmmin_heap(struct heap  *p)
{
  int min;
  //printf("sz before decrement:%d\n",p->sz);
  (p->sz)--;
  //printf("sz after decrement:%d\n",p->sz);
  min = p->item[0];
  p->item[0] = p->item[p->sz];
  p->item[p->sz] = min;
  //printf("item[0]= %d, Removed = %d\n", p->item[0], min);
  siftdown(p,0);
  //printf("sz at end of rmmin_heap:%d\n",p->sz);
  return(min); 
}
