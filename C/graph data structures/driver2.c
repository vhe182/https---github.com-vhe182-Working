/*
 *
 *
 *
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "graph.h"

int main(int numc, char *argv[])
{
  FILE *fpin;
  struct graph *g;
  int u, v, i;
  char n[10], e[10];

  if(numc != 2)
  {
    fprintf(stdout,"Usage: %s <filename>\n",argv[0]);
    exit(-1);
  }
  
  if( (fpin = fopen(argv[1],"r")) == NULL)
  {
    fprintf(stderr,"Error: Unable to read file");
    exit(-1);
  }
  
  if(fscanf(fpin,"%s %d %s %d", n, &u, e, &v) != 4)
  {
    fprintf(stderr,"Error: Unable to read first line");
    exit(-1);
  }
  
  if( (g = init_graph(u)) == NULL)
  {
    fprintf(stderr,"Error: Unable to malloc graph\n");
    exit(-1);
  }
  
  for( i = 0; i < u; i++)
  {
    if(insert_vertex(i,&g) < 0)
    {
      fprintf(stderr,"Error: Unable to insert vertex %d\n", i);
      exit(-1);
    }
  }

  while( fscanf(fpin,"%d %d", &u, &v) == 2)
  {
    if( insert_edge(u,v,g) < 0)
    {
      fprintf(stderr,"Error: Unable to insert edge (%d,%d)\n", u, v);
      exit(-1);
    }
  }
/**************  
  printf("Printing Graph\n");
  print_graph(g);
**************/
  while( scanf("%d %d", &u,&v) == 2)
  {
    if( prtsrtpath(g,u,v) < 0)
    {
      fprintf(stderr,"Error in prtsrtpath: (%d,%d)\n",u,v);
      exit(-1);
    }
  }
  fclose(fpin); 
  //printf("Freeing Graph\n");
  free_graph(g);
  //printf("Graph Freed\n");
  return (0);
} 
