/*
 *  driver.c tester
 * 
 *  by Victor Hugo Estrada
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "graph.h"

int main(int numc, char *argv[])
{
  struct graph *g;
  int u, v;
  int i;
  char n[10], e[10];

  if( scanf("%s %d %s %d", n, &u, e, &v) != 4)
  { 
    fprintf(stdout,"Usage: Nodes: <# of nodes> Edges: <# of edges>\n");
    exit(-1);
  }
  
  if( (g = init_graph(u)) == NULL)
  {
    fprintf(stderr,"Error: Unable to malloc graph\n");
    exit(-1);
  }

  //inserting vertices
  for( i = 0; i < u; i++)
  {
    if(insert_vertex(i,&g) < 0)
    {
      fprintf(stderr,"Error: Unable to insert vertex (%d)\n",i);
      exit(-1);
    }
  }

  //inserting edges
  while( scanf("%d %d", &u,&v) == 2)
  {
    if(insert_edge(u,v,g) < 0)
    {
      fprintf(stderr,"Error: Unable to insert edge (%d,%d)\n",u,v);
      exit(-1);
    }
  }

  printf("Printing graph\n");
  print_graph(g);

  printf("Printing Depth First Traversal\n");
  dftraversal(g);

  printf("Printing Breath First Traversal\n");
  bftraversal(g);

  printf("Freeing graph\n");
  free_graph(g);
  printf("Graph freed\n");
  return(0);
} 
