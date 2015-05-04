#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dlist.h"


int main(int numc, char *argv[])
{
  FILE *fp;
  struct dlist *b;
  char line[BUFSZ];
  int i;

  if(numc != 2)
  {
    fprintf(stderr,"Usage: %s   <filename>\n", argv[0]);
    return(-1);
  }
  if((fp = fopen(argv[1],"r")) == NULL)
  {
    perror(argv[1]);
    exit(-1);
  }
  if((b = init_dlist(INITSZ)) == NULL)
  {
    perror("Unable to malloc dlist");
    return(-1);
  }
  while(fgets(line, BUFSZ-1, fp) != NULL)
  {
    if(ins_dlist(line, &b))
    {
      perror("Unable to realloc dlist");
      return(-1);
    }
  }
  qsort(&(b->item), b->sz, sizeof(char)*BUFSZ, strcmp);
  if(b->sz == 4)
  {
    b->item[4][0] = '\0';
    b->sz--;
  }else if(b->sz > 4)
  {
    for(i = 4; i < (b->sz) - 1 ; i++)
    {
      strcpy(&(b->item[i]), &(b->item[i+1]));
    }
    b->item[i][0] = '\0';
    b->sz--;
  }
  prt_dlist(b);
  free(b);
  fclose(fp);
  return(0);
}
