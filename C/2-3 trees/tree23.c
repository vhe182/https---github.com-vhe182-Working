/**************************************
 *
 *
 **************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "tree23.h"

FILE *debug;
/******************TREE*FUNCTIONS**************/
int init23(char *file)
{
  if(file == NULL)
    debug = stdout;
  else{
    if((debug = fopen(file,"w")) == NULL)
    {
      perror(file);
      return(-1);
    }
  }
  return 0;
}
struct node *avail23(void)
{
  struct node *node; 
  
  node = (struct node*)malloc((size_t)sizeof(struct node));
  if(node == NULL)
  {
    perror("Error mallocing for node");
    return(NULL);
  }
  
  node->data = (struct coords*)malloc((size_t)sizeof(struct coords));
  if(node->data == NULL)
  {
    perror("Error mallocing for data");
    return(NULL);
  }

  node->son1 = NULL;
  node->son2 = NULL;
  node->son3 = NULL;

  return node;
}
void indent23(int h)
{
  int i;
  for( i = 0; i < h; i++)
    fprintf(debug,"%s","  ");
}
void print_tree23(struct node *node, int h)
{
  if(node == NULL)
  {
    fprintf(debug,"tree: NULL\n");
    return;
  }
  if(node->son1 == NULL)
  {  
    fprintf(debug,"(%d,%d,%d)	%.1f\n", node->data->x, node->data->y, node->data->z, node->data->dist);


    return;
  }
  h++;
  print_tree23(node->son1,h);
  print_tree23(node->son2,h);
  if(node->son3 != NULL)
    print_tree23(node->son3,h);
}
int height23(struct node *node)
{
  int h;
  if(node == NULL)
    return(-1);
  h = 0;
  while(node->son1 != NULL)
  {
    h++;
    node = node->son1;
  }
  return h;
}
void free23(struct node *p)
{
  if(p == NULL)
    return;
  free23(p->son1);
  free23(p->son2);
  free23(p->son3);
  free(p->data);
  free(p);
}
int valid23(struct node *node)
{
  if(node == NULL)
    return(TRUE);
  if(ckdepth23(node, height23(node)) == -1)
  {
    fprintf(debug,"ERROR: Tree failed depth test\n");
    return(FALSE);
  }
  if(ckindex23(node) == -1)
  {
    fprintf(debug,"ERROR: Tree failed index test\n");
    return(FALSE);
  }
  initial = TRUE;
  if(ckorder23(node) == -1)
  {
    fprintf(debug,"ERROR: Tree failed order test\n");
    return(FALSE);
  }
  return(TRUE);
}
float min23(struct node *node)
{
  while(node->son1 != NULL)
    node = node->son1;
  return(node->data->dist);
}
struct node *locatemin23(struct node *node)
{
  if(node == NULL)
    return NULL;
  while(node->son1 != NULL)
    node = node->son1;
  return(node);
}
float max23(struct node *node)
{
  while(node->son1 != NULL)
  {
    if(node->son3 != NULL)
      node = node->son3;
    else
      node = node->son2;
  }
  return(node->index1);
}
struct node *locatemax23(struct node *node)
{
  if(node == NULL)
    return(NULL);
  while(node->son1 != NULL)
  {
    if(node->son3 != NULL)
      node = node->son3;
    else
      node = node->son2;
  }
  return(node);
}
int ckorder23(struct node *node)
{
  if(node->son1 == NULL)
  {
    if(initial)
    {
      initial = 0;
      last = node->index1;
      return(0);
    }else{
      if(last < node->index1)
      {
        last = node->index1;
        return(0);
      }else{
        return(-1);
      }
    }
  }
  if(ckorder23(node->son1))
    return(-1);
  if(ckorder23(node->son2))
    return(-1);
  if(node->son3 != NULL)
    if(ckorder23(node->son3))
      return(-1);
  return(0);
}
int ckdepth23(struct node *node, int h)
{
  if(node->son1 == NULL)
  {
    if(h == 0)
      return(0);
    else
      return(-1);
  }
  if(ckdepth23(node->son1, h-1))
    return(-1);
  if(ckdepth23(node->son2, h-1))
    return(-1);
  if(node->son3 != NULL)
    if(ckdepth23(node->son3, h-1))
      return(-1);
  return(0);
}
int ckindex23(struct node *node)
{
  if(node->son1 == NULL)
    return(0);
  if(max23(node->son1) >= node->index1)
    return(-1);
  if(node->index1 > min23(node->son2))
    return(-1);
  if(node->son3 != NULL)
  {
    if(max23(node->son2) >= node->index2)
      return(-1);
    if(node->index2 > min23(node->son3))
      return(-1);
  }
  if(ckindex23(node->son1))
    return(-1);
  if(ckindex23(node->son2))
    return(-1);
  if(node->son3 != NULL)
    if(ckindex23(node->son3))
      return(-1);
  return(0);
}
struct node *search23(float x, struct node *node)
{
  if(node == NULL)
    return(NULL);
  if(node->son1 == NULL)
    return(NULL);
  while(node->son1->son1 != NULL)
  {
    if(x < node->index1)
      node = node->son1;
    else
      if(node->son3 == NULL || x < node->index2)
        node = node->son2;
      else
        node = node->son3;
  }
  return(node);
}
struct node *insert23(struct node **root, struct coords *new)
{
  struct node *newroot;
  struct node *oldroot;
  struct node *leaf;
  struct node *split;
  float minback;

  // NULL node case
  if(*root == NULL)
  {
    *root = avail23();
    (*root)->data->x = new->x;
    (*root)->data->y = new->y;
    (*root)->data->z = new->z;
    (*root)->data->dist = (*root)->index1 = new->dist; 
    return(*root);
  }
  // 1 node case
  if((*root)->son1 == NULL)
  {
    if(abs((*root)->index1 - calcdist(new)) <= MAXERR)
      return(NULL);
    newroot = avail23();
    leaf = avail23();
    leaf->data->x = new->x;
    leaf->data->y = new->y;
    leaf->data->z = new->z;
    leaf->index1 = leaf->data->dist = new->dist;
     
    if( leaf->index1 > (*root)->index1 )
    {
      newroot->son1 = *root;
      newroot->index1 = new->dist;
      newroot->son2 = leaf;
    }else{
      newroot->son1 = leaf;
      newroot->index1 = (*root)->index1;
      newroot->son2 = *root;
    }
    *root = newroot;
    return(leaf);
  }
  //General case
  leaf = addson(new, *root, &split, &minback);
  if( leaf == NULL)
    return(NULL);
  if(split != NULL)
  {
    oldroot = *root;
    *root = avail23();
    (*root)->son1 = oldroot;
    (*root)->son2 = split;
    (*root)->son3 = NULL;
    (*root)->index1 = minback;
  }
  return(leaf);
}
struct node *addson(struct coords *new, struct node *node, struct node **split, float *low)
{
  struct node *leaf;
  struct node *nodeback;
  struct node *w;
  float lowback;
  int child;

  *split = NULL;
  if(node->son1 == NULL)
  {
    if(fabs(node->index1 - new->dist) <= MAXERR)
      return(NULL);
    *split = avail23();
    if(node->index1 <= new->dist)
    {
      (*split)->index1 = new->dist;
      (*split)->data->x = new->x;
      (*split)->data->y = new->y;
      (*split)->data->z = new->z;
      (*split)->data->dist = new->dist;
      *low = new->dist;
      return(*split);
    }else{
      (*split)->index1 = (*split)->data->dist = node->index1; 
      (*split)->data->x = node->data->x;
      (*split)->data->y = node->data->y;
      (*split)->data->z = node->data->z;
      node->index1 = node->data->dist = new->dist;
      node->data->x = new->x;
      node->data->y = new->y;
      node->data->z = new->z;
      *low = (*split)->index1;
      return(node);
    }
  }
  if(new->dist < node->index1)
  {
    child = 1;
    w = node->son1;
  }else{
    if(node->son3 == NULL || new->dist < node->index2)
    {
      child = 2;
      w = node->son2;
    }else{
      child = 3;
      w = node->son3;
    }
  }
  leaf = addson(new, w, &nodeback, &lowback);
  if(leaf == NULL)
    return(NULL);
  if(nodeback != NULL)
  {
    if(node->son3 == NULL)
    {
      if(child == 2)
      {
        node->son3 = nodeback;
        node->index2 = lowback;
      }else{
        node->son3 =node->son2;
        node->index2 = node->index1;
        node->son2 = nodeback;
        node->index1 = lowback;
      }
    }else{
      (*split) = avail23();
      if(child == 3)
      {
        (*split)->son1 = node->son3;
        (*split)->son2 = nodeback;
        (*split)->son3 = NULL;
        (*split)->index1 = lowback;
        *low = node->index2;
        node->son3 = NULL;
      }else{
        (*split)->son2 = node->son3;
        (*split)->index1 = node->index2;
        (*split)->son3 = NULL;
        node->son3 = NULL;
      }
      if(child == 2)
      {
        (*split)->son1 = nodeback;
        *low = lowback;
      }
      if(child == 1)
      {
        (*split)->son1 = node->son2;
        *low = node->index1;
        node->son2 = nodeback;
        node->index1 = lowback;
      }
    }
  }
  return(leaf);
}
void delete23(struct node **tree, float x)
{
  struct node *node;

  //NULL case
  if(*tree == NULL)
    return;
  
  //1-Node case
  if((*tree)->son1 == NULL)
  {
    if(fabs((*tree)->index1 - x) <= MAXERR)
    { 
      (void)free((void*)*tree);
      *tree = NULL;
    }
    return;
  }
  //General case
  if(delete1(*tree,x))
  {
    node = *tree;
    *tree = (*tree)->son1;
    
    (void)free((void*)(node->data));
    (void)free((void*)node);
  }
  return;
}
int delete1(struct node *node, float x)
{
  int del1;
  int oneson;
  struct node *w;
  struct node *z;
  struct node *y;


  del1 = FALSE;
  if(node->son1->son1 == NULL)
  {
    if(fabs(node->son1->index1 - x) <= MAXERR)
    {
      
      (void)free((void*)(node->son1->data));
      (void)free((void*)(node->son1));
      node->son1 = node->son2;
      node->son2 = node->son3;
      node->son3 = NULL;
      node->index1 = node->index2;
      if(node->son2 == NULL)
        del1 = TRUE;
    }else{
      if(fabs(node->son2->index1 - x) <= MAXERR)
      {
        
        (void)free((void*)(node->son2->data));
        (void)free((void*)(node->son2));
        node->son2 = node->son3;
        node->son3 = NULL;
        node->index1 = node->index2;
        if(node->son2 == NULL)
          del1 = TRUE;
      }else{
        if(node->son3 != NULL && fabs(node->son3->index1 - x) <= MAXERR)
        {
          
          (void)free((void*)(node->son3->data));
          (void)free((void*)(node->son3));
          node->son3 = NULL;
        }
      }
    }
  }else{
    if( x < node->index1)
    {
      w = node->son1;
    
    }else{
      if(node->son3 == NULL || x < node->index2)
      {
        w = node->son2;
      
      }else{
        w = node->son3;
      }
    }
    oneson = delete1(w, x);
    if(oneson)
    {
      if(w == node->son1)
      {
        if((y = node->son2)->son3 != NULL)
        {
          w->son2 = y->son1;
          y->son1 = y->son2;
          y->son2 = y->son3;
          y->son3 = NULL;
          w->index1 = node->index1;
          node->index1 = y->index1;
          y->index1 = y->index2;
        }else{
          y->son3 = y->son2;
          y->son2 = y->son1;
          y->son1 = w->son1;
          y->index2 = y->index1;
          y->index1 = node->index1;
          node->index1 = node->index2;
          node->son1 = node->son2;
          node->son2 = node->son3;
          node->son3 = NULL;
          
          (void)free((void*)(w->data));
          (void)free((void*)w);
          if(node->son2 == NULL)
            del1 = TRUE;
        }
      }else
        if(w == node->son2)
        {
          if( (y = node->son1)->son3 != NULL)
          {
            w->son3 = w->son2;
            w->son2 = w->son1;
            w->son1 = y->son3;
            y->son3 = NULL;
            w->index1 = node->index1;
            node->index1 = y->index2;
          }else{
            if( (z = node->son3) != NULL && z->son3 != NULL)
            {
              w->son2 = z->son1;
              z->son1 = z->son2;
              z->son2 = z->son3;
              z->son3 = NULL;
              w->index1 = node->index2;
              node->index2 = z->index1;
              z->index1 = z->index2;
            }else{
              y->son3 = w->son1;
              node->son2 = z;
              node->son3 = NULL;
              y->index2 = node->index1;
              node->index1 = node->index2;
              
              (void)free((void*)(w->data));
              (void)free((void*)w);
              if( z == NULL)
                del1 = TRUE;
            }
          }
        }else{
          if( (y = node->son2)->son3 != NULL)
          {
            w->son2 = w->son1;
            w->son1 = y->son3;
            y->son3 = NULL;
            w->index1 = node->index2;
            node->index2 = y->index2;
          }else{
            y->son3 = w->son1;
            node->son3 = NULL;
            y->index2 = node->index2;
            
            (void)free((void*)(w->data));
            (void)free((void*)w);
          }
        }
    }
  }
  return(del1);
}
/**************MATH*FUNCTIONS**********************/
float calcdist(struct coords *new)
{
   return sqrt(pow((new->x - base->x),2) + pow((new->y - base->y),2) + pow((new->z - base->z),2));
}
