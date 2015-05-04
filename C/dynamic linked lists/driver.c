/*
 *  Assignment 5
 *  written by Victor Hugo Estrada
 *  This program uses files:
 *  llist.c, llist.h, sstor.c, sstor.h
 *  
 *  Program reads input file from command line
 *  and stores each line of text (max 1022 chars per line)
 *  into a dynamic list.  For every line that is read,
 *  the index of the beginning letter of the line is
 *  stored in a doubly linked list in an order
 *  dictated by the strcmp function.  Program 
 *  will then delete the 5th string from the 
 *  doubly linked list (the string will still be 
 *  located in the dynamic list) and then print
 *  out the ordered lines of text.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "llist.h"

#define BUFSIZ    1024

int sreplace(char newc, char oldc, char *s);

int main(int numc, char *argv[])
{
  FILE *fp;
  struct llist *t; 
  char line[BUFSIZ];

  //Checks for command line arguments
  if(numc != 2)
  {
    fprintf(stderr,"Usage: %s   <filename>\n", argv[0]);
    return(-1);
  }
 
  //Checks for correct file opening
  if((fp = fopen(argv[1],"r")) == NULL)
  {
    perror(argv[1]);
    exit(-1);
  }
 
  /* 
   * Initializes and Checks for proper initialization
   * of the doubly linked struct and dynamic list
   */
   if((t = init_llist()) == NULL)
  {
    perror("Unable to initialize dlist and llist");
    return(-1);
  } 
  
  //Loop: Read one line per loop, inputs into D-linked struct
  while(fgets(line, BUFSIZ-1, fp) != NULL)
  {
    //Overflow check and removal of '\n'
    if(sreplace('\0', '\n', line) != 1)
    {
      fprintf(stdout,"ERROR: Max characters per line 1022\n");
      exit(-1);
    } 
    //Place string into D-linked struct/Dynamic array
    if(ins_llist(line, t) == NULL)
    {
      perror("Unable to insert into llist");
      exit(-1);
    }
  } 
  del_llist(5,t);
  prt_llist(t);
  free_llist(t);
  fclose(fp);
  return(0);
}
int sreplace(char newc, char oldc, char *s)
{
  int i=0;  //  Tracks number of replacements.
  while(*s != '\0')
  {
    if(*s == oldc)
    {
      i++;
      *s = newc;
    }
    s++;
  }
  return i;
}
