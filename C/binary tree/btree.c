/*
 *
 *
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "btree.h"

struct node *ins_tree(int data, struct node **t)
{
  struct node **p, *q;
  p = t;
  while(*p != NULL)
  {
    if((*p)->item == data)
      return (*p);
    if(data < (*p)->item)
      p = &((*p)->left);
    else
      p = &((*p)->right);
  }
  q = malloc(sizeof(struct node));
  if(q == NULL)
    return NULL;
  *p = q;
  q->item = data;
  q->left = NULL;
  q->right = NULL;
  return(q);
}
void free_tree(struct node *t)
{
  if(t == NULL)
    return;
  free_tree(t->left);
  free_tree(t->right);
  free(t);
}
int reverse(struct node *t)
{
  if(t == NULL)
    return (-1);
  int h = height(t);
  p_reverse(t, h);
  return (0);
}
int p_reverse(struct node *t, int h)
{
  struct node *tmp;
  if(t == NULL || h == 0)
    return 0;
  tmp = t->left;
  t->left = t->right;
  t->right = tmp;
  p_reverse(t->left, h-1);
  p_reverse(t->right, h-1);
  return(0);
}
int height(struct node *t)
{
  if(t == NULL)
    return (-1);
  int hl = height(t->left);
  int hr = height(t->right);
  if(hl > hr)
    return (hl+1);
  else
    return (hr+1);
}
int width(struct node *t)
{
  if(t == NULL)
    return 0;
  int h = height(t);
  int i = 1, wcur = 0, wmax = 0;
  while( i++ <= h)
  {
    wcur = p_width(t, i);
    if(wcur > wmax)
      wmax = wcur;
  }
  return wmax;
}
int p_width(struct node *t, int l)
{
  if(t == NULL)
    return 0;
  if( l == 1)
    return 1;
  return p_width(t->left, l-1) + p_width(t->right, l-1);
}
void print_tree(struct node *t)
{
  if( t == NULL)
  {
    fprintf(stdout,"Null Tree\n");
    return;
  }
  p_tree(t, 0);
}
void p_tree(struct node *t, int h)
{
  int i;
  if(t == NULL)
    return;
  for(i = 0; i < h; i++)
    fprintf(stdout,"  ");
  fprintf(stdout,"%d\n", t->item);
  p_tree(t->left, h+1);
  p_tree(t->right, h+1);
}
