/*
 *  graph.h
 * 
 *  Written by Victor Hugo Estrada
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fifo.h"

struct enode{
  int vndx;
  int dist;
  struct enode *next;
};

struct vnode{
  int item;
  int visited;
  struct enode *edge;
};

struct graph{
  int sz;
  int maxsz;
  struct vnode vn[1];
};

#define INITGRSZ    1500000 
#define INCRGRSZ    500000

#define GRAPHSZ(n)  (sizeof(struct graph) + ((n)-1)*sizeof(struct vnode))
#define INCR(n) ((n)<10?1:((n)<100?2:((n)<1000?3:((n)<10000?4:5))))

struct graph *init_graph(int num);
void print_graph(struct graph *g);
struct enode *init_enode(int w);
int insert_vertex(int x, struct graph **g);
int insert_edge(int u, int v, struct graph *g);
void free_graph(struct graph *g);
void dftraversal(struct graph *g);
void dft(struct graph *g, struct vnode *v, int id);
int unvisited(struct graph *g);
void indent(int n);
int bftraversal(struct graph *g);
int prtsrtpath(struct graph *g, int src, int dest);
void prtpred(int src, int dst, int *p);

struct fifo *f;
