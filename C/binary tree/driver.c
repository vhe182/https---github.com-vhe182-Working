/*
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "btree.h"

int main(void)
{
  int data;
  struct node *t;
  t = NULL;
  while(scanf("%d", &data) >= 0)
  {
    if(ins_tree(data, &t) == NULL)
    {
      fprintf(stderr,"Error inserting %d\n", data);
      exit(-1);
    }
  }
  print_tree(t);
  fprintf(stdout,"\n");
  fprintf(stdout,"height = %d", height(t));
  fprintf(stdout,"\n");
  fprintf(stdout,"width = %d", width(t));
  fprintf(stdout,"\n");
  reverse(t);
  print_tree(t);
  free_tree(t);
  return(0);
}
