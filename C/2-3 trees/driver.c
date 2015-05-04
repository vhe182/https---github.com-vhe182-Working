/*
 *  23 Tree functions
 *  paired with: 23tree.h, driver.c
 *
 *  Written by Victor Hugo Estrada
 * 
 *     
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "tree23.h"

struct coords *base;

int main(int numc, char *argv[])
{
  FILE *fp;
  struct node *tree;
  struct coords *buf;
  extern FILE *debug;  
  
  if(numc < 5 || numc > 6)
  {
    fprintf(stdout,"Usage: %s <x> <y> <z> <input file>\n", argv[0]);
    exit(-1);
  }
  
  if((fp = fopen(argv[4],"r")) == NULL)
  {
    perror("Unable to open file");
    exit(-1);
  }
  if(numc == 5)
    (void)init23(NULL);
  else{
    if(init23(argv[6]))
    {
      perror(argv[6]);
      return(-1);
    }
  } 
  
  base = malloc((size_t)sizeof(struct coords));
  buf = malloc((size_t)sizeof(struct coords));
  base->x = atoi(argv[1]);
  base->y = atoi(argv[2]);
  base->z = atoi(argv[3]);
  tree = NULL;
 
  if(numc == 5)
    (void)init23(NULL);
  else if(init23(argv[5]))
  {
    perror(argv[5]);
    exit(-1);
  }
  
  //fprintf(debug,"BASEPOINT\n(%d,%d,%d)\n\nOTHER POINTS\n", base->x, base->y, base->z);
  if(valid23(tree) == -1)
  {
    fprintf(debug,"Error during first valid23(tree)\n");
    exit(-1);
  }
  
  while(fscanf(fp,"(%d,%d,%d)\n", &(buf->x), &(buf->y), &(buf->z)) == 3)
  {
    buf->dist = calcdist(buf); 
    //fprintf(debug,"(%d,%d,%d)	%.1f\n", buf->x, buf->y, buf->z, buf->dist);
    insert23(&tree, buf);    
    //fprintf(debug,"tree after insert:\n");
    //print_tree23(tree, height23(tree));
  }
  if(valid23(tree) == -1)
  {
    fprintf(debug,"2nd valid23 check: invalid tree\n");
    exit(-1);
  } 
  delete23(&tree, 0.0); 
  print_tree23(tree, height23(tree));
  fclose(fp);
  free(base);
  free(buf);
  free23(tree); 
  //free(debug);
  return(0);
}
