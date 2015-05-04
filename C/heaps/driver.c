/*
 *  Program written by Victor Hugo Estrada
 *
 *  Assignment 8: Dynamic Structures - Heaps
 *  Files Associated: driver.c, heap.c, heap.h, Makefile
 *  
 *  Summary: Program will receive integers and place them
 *  into a dynamic list until the "build command is given"
 *  upon which a minimum heap will be organized.  Inserting
 *  integers after the build command is given can be done
 *  in this format:
 *   
 *  insert 100
 *  
 *  extracting the minimum value can be executed by giving
 *  the command:
 *  
 *  extract  
 *
 *  When finished, exit out of the loop by typing: 
 *
 *  quit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "heap.h"

int main(void)
{
  int num;
  char buf[1028]; 
  struct heap *p;
  
  if((p = init_heap(INITHSZ)) == NULL)
  {
    fprintf(stderr,"Failure to malloc initial heap\n");
    exit(-1);
  }
  
  while(scanf("%d",&num) == 1)
  {
    insert_heap(num, &p);
    //fprintf(stderr,"%d in\n", p->item[(p->sz)-1]);
  }
  
  scanf("%s",buf);

  if( strcmp(buf,"build") == 0)
    build_heap(p);
  else{
    fprintf(stderr,"Error comparing buf and build\n");
    exit(-1);
  }
  
  //debug_heap(p); 
  if( valid_heap(p) == 0)
  {
    fprintf(stderr,"Failed valid heap check\n");
    exit(-1);
  }
  
  //print_heap(p);
  num = NIL;
  while(scanf("%s",buf) == 1)
  {
    //fprintf(stderr,"string: %s", buf);
    
    if(strcmp(buf,"insert") == 0)
    {  
      if(scanf("%d",&num) == 1 && num != NIL)
      { 
        //fprintf(stderr,"%d\n",num);
        if( (insert_heap(num, &p) ) == NIL)
        {
          fprintf(stderr,"Error inserting %d\n",num);
          exit(-1);
        }
        //print_heap(p);
      }
    }
    
    if(strcmp(buf,"extract") == 0)
    {
      num = rmmin_heap(p);
      fprintf(stdout,"%d\n",num);
      //print_heap(p);
    }
    num = NIL;
    
    if(strcmp(buf,"quit") == 0)
      break;
  }
  //print_heap(p);
  free(p);
  return (1); 
}
