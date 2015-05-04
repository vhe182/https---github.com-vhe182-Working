/*
 *  graph.c
 * 
 *  Written by Victor Hugo Estrada
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "graph.h"


struct graph *init_graph(int num)
{
  struct graph *g;
  
  if((g = malloc(GRAPHSZ((size_t)num))) == NULL)
  {
    perror("init_graph:  Malloc error");
    return(NULL);
  }
  
  g->sz = 0;
  g->maxsz = num;
  return(g);
}
void print_graph(struct graph *g)
{
  struct enode *e;
  int i;

  for( i = 0; i < g->sz; i++)
  {
    printf("vertex = %d\n", g->vn[i].item);
    e = g->vn[i].edge;
    
    while(e != NULL)
    {
      printf("\tedge = (%d,%d)\n",g->vn[i].item, g->vn[e->vndx].item);
      e = e->next;
    }
  }
}
struct enode *init_enode(int w)
{
  struct enode *e;
  
  if(( e = malloc((size_t)sizeof(struct enode))) == NULL)
  {
    perror("init_enode: Malloc error");
    return(NULL);
  }
  
  e->next = NULL; 
  e->vndx = w;
  return(e);
}
int insert_vertex(int x, struct graph **g)
{
  struct graph *tg;
  int i;

  //Check if x already exists in graph
  for( i = 0; i < (*g)->sz; i++)
  {
    if( (*g)->vn[i].item == x)
    {
      fprintf(stderr,"Error in insert_vertex(): value already in graph\n");
      return(-1);
    }
  }

  if( (*g)->sz == (*g)->maxsz)
  {
    tg = realloc(*g, (size_t)GRAPHSZ((*g)->maxsz + INCRGRSZ));
    if( tg == NULL)
    {
      perror("insert_vertex: Realloc error");
      return(-1);
    }
    *g = tg;
    (*g)->maxsz += INCRGRSZ;
  }
  
  (*g)->vn[(*g)->sz].item = x;
  (*g)->vn[(*g)->sz].visited = 0;
  (*g)->vn[(*g)->sz++].edge = NULL;
  return(0);
}
int insert_edge(int u, int v, struct graph *g)
{
  int i, iu, iv;
  struct enode *e;

  //check that (u,v) exist as vertices
  iu = -1;
  iv = -1;
  for( i = 0; i < g->sz; i++)
  {
    if(iu >= 0 && iv >= 0)
      break;
    if(g->vn[i].item == u)
      iu = i;
    if(g->vn[i].item == v)
      iv = i;
  }
  if(iu < 0 || iv < 0)
  {
    fprintf(stderr,"Error in insert_edge(): nodes not in graph\n");
    return(-1);
  }
  
  //check that (u,v) has not already been inserted
  e = g->vn[iu].edge;
  while(e != NULL)
  {
    if( e->vndx == iv)
    {
      fprintf(stderr,"Error in insert_edge(): edge already in graph\n");
      return(-1);
    }
    e = e->next;
  }
  
  //Insert (u,v) into graph
  if((e = init_enode(iv)) == NULL)
  {
    fprintf(stderr,"Error in insert_edge(): Unable to init enode\n");
    return(-1);
  }
  
  //Insert e at front of u's edge list
  e->next = g->vn[iu].edge;
  g->vn[iu].edge = e;

  return(0);
}
void free_graph(struct graph *g)
{
  struct enode *e, *olde;
  int i;
  
  //Free edge nodes
  for( i = 0; i < g->sz; i++)
  {
    e = g->vn[i].edge;
    while( e != NULL)
    {
      olde = e;
      e = e->next;
      free(olde);
    }
  }
  
  //Free graph
  free(g);
}
void dftraversal(struct graph *g)
{
  int i;

  for( i = 0; i < g->sz; i++)
    g->vn[i].visited = 0;
  i = 0;
  printf("\n");
  while( i != -1)
  {
    printf("%d", g->vn[i].item);
    dft(g, &(g->vn[i]), INCR(g->vn[i].item));
    i = unvisited(g);
  }
}
void dft(struct graph *g, struct vnode *v, int id)
{
  struct enode *e;
  int first;
 
  first = 1;
  v->visited = 1;
  e = v->edge;
  while(e != NULL)
  {
    if( !g->vn[e->vndx].visited)
    {
      if(first)
      {
        first = 0;
      }else{
        indent(id);
      }
    
      printf("-->%d", g->vn[e->vndx].item);
      id += 3 + INCR(g->vn[e->vndx].item);
      dft(g,&(g->vn[e->vndx]),id);
      id -= 3 + INCR(g->vn[e->vndx].item);
    }
    e = e->next;
  }
  if(first)
    printf("\n");
}
int unvisited(struct graph *g)
{
  int i;
  
  for(i = 0; i < g->sz; i++)
  {
    if( g->vn[i].visited == 0)
    {
      return(i);
    }
  }
  return(-1);
} 
void indent(int n)
{
  int i;
  for( i = 0; i < n; i++)
    printf("%s"," ");
}
int bftraversal(struct graph *g)
{
  int i;
  struct enode *e;
  struct vnode *v;
  int ndx;
  int level;

  if( (f = init_fifo(g->sz)) == NULL)
  {
    perror("bfttraversal: fifo Malloc error");
    return(-1);
  }
  
  //Reset all visited fields to 0
  for( i = 0; i < g->sz; i++)
    g->vn[i].visited = 0;
  
  i = 0;
  printf("\n");
  while(i != -1)
  {
    g->vn[i].visited = 1;
    level = 1;
    insert_fifo(i,&f);

    while(f->sz > 0)
    {
      extract_fifo(&ndx,f);
      v = &(g->vn[ndx]);
      printf("%d(%d)  ", v->item, v->visited);
      level = v->visited + 1;
      e = v->edge;
      
      while( e != NULL)
      {
        if( !g->vn[e->vndx].visited)
        {
          g->vn[e->vndx].visited = level;
          insert_fifo(e->vndx,&f);
        }
        e = e->next;
      }
      
    }
    i = unvisited(g);
    printf("\n");
  }
  free(f);
  return(0);
}
int prtsrtpath(struct graph *g, int src, int dest)
{
 
  struct enode *e;
  struct vnode *v;
  int i, ndx, level, curv;
  int *pred;

  if( (f = init_fifo(g->sz)) == NULL)
  {
    perror("prtsrtpath: fifo Malloc error");
    return(-1);
  }
  
  if( (pred = malloc(g->sz*sizeof(int))) == NULL)
  {
    perror("prtsrtpath: pred value Malloc error");
    return(-1);
  }

  //Set all preds to -1
  for( i = 0; i < g->sz; i++)
    pred[i] = -1;

  //Set all visited to 0
  for( i = 0; i < g->sz; i++)
    g->vn[i].visited = 0;

  curv = src;
  g->vn[curv].visited = 1;
  level = 1;
  insert_fifo(curv, &f);
  
  while(f->sz > 0)
  {
    extract_fifo(&ndx, f);
    v = &(g->vn[ndx]);
    level = v->visited + 1;
    e = v->edge;
    while( e != NULL)
    {
      if( !g->vn[e->vndx].visited)
      {
        g->vn[e->vndx].visited = level;
        pred[e->vndx] = ndx;
        insert_fifo(e->vndx, &f);
      }
      e = e->next;
    }
  }
  
  free(f);
  prtpred(src, dest, pred);
  free(pred);
  return(0);
}
void prtpred(int src, int dst, int *p)
{
  if(p[dst] == -1)
  {
    printf("No path from %d to %d\n", src, dst);
    return;
  }
  printf("%d",dst);
  while(p[dst] != -1)
  {
    dst = p[dst];
    printf(" <-- %d", dst);
  }
  printf("\n");
}
