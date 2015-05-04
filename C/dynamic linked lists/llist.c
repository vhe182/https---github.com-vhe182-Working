#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "llist.h"
#include "sstor.h"

struct llist *init_llist(void)
{
  struct llist *l;
  l = malloc(sizeof(struct llist));
  if(l == NULL)
    return NULL;

  l->head = malloc(sizeof(struct lnode));
  if(l->head == NULL)
  {
    free(l);
    return NULL;
  }

  l->tail = malloc(sizeof(struct lnode));
  if(l->tail == NULL)
  {
    free(l->head);
    free(l);
    return NULL;
  }

  l->head->next = l->tail;
  l->head->prev = NULL;
  l->tail->prev = l->head; 
  l->tail->next = NULL;

  c = init_dlist();
  if(c == NULL)
  {
    free(l->head);
    free(l->tail);
    free(l);
    return NULL;
  }
  return(l);
}
struct lnode *ins_llist(char *str, struct llist *l)
{
  struct lnode *a, *b;
  
  b = malloc(sizeof(struct lnode));
  if(b == NULL)
    return NULL;
  
  a = l->head->next;
  while(a->next != NULL && strcmp(str, &(c->line[a->index])) >= 0)
    a= a->next;
  if(ins_dlist(str, &c) == -1)
  {
    perror("Unable to realloc dlist");
    exit(-1);
  }
  b->index = c->sz - (strlen(str) + 1);
  b->next = a;
  b->prev = a->prev;
  a->prev->next = b;
  a->prev = b;

  return(b);
}
int del_llist(int num, struct llist *l)
{
  struct lnode *a;
  int i = 1;
  a = l->head->next;
  while(a->next != NULL && i < num)
  {
    a = a->next;
    i++;
  }
  if(a->next == NULL || i != num)
    return (-1);
  
  a->prev->next = a->next;
  a->next->prev = a->prev;
  free(a);
  return(0);
}
void prt_llist(struct llist *l)
{
  struct lnode *p;
  p = l->head->next;
  while(p->next != NULL)
  {
    fprintf(stdout,"%s\n", &(c->line[p->index]));
    p = p->next;
  }
}
void free_llist(struct llist *l)
{
  struct lnode *s;
  s = l->head->next;
  while(s->next != NULL)
  {
    free(s->prev);
    s = s->next;
  }
  free(s->prev);
  free(s);
  free(l);
  free(c);
}
int valid_llist(struct llist *l)
{
  struct lnode *p;
  
  if(l == NULL || l->head == NULL || l->tail == NULL ||
     l->head->next == NULL || l->tail->prev == NULL ||
     l->head->prev != NULL || l->tail->next != NULL)
  {
    return(0);
  }
  p = l->head->next;
  while(p->next != NULL)
  {
    if(p->prev == NULL || p->prev->next != p || p->next->prev != p)
    {
      return(0);
    }
    p = p->next;
  }
  if(p != l->tail)
  {
    return(0);
  } 
  return(1);
}
