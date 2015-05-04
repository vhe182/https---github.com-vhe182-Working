/*
 *  tree23.h
 *  header file for tree23.c
 */
struct node{
  float index1;
  float index2;
  struct coords *data;
  struct node *son1;
  struct node *son2;
  struct node *son3;
};
struct coords{
  int x;
  int y;
  int z;
  float dist;
};

#define TRUE    1
#define FALSE   0
#define MAXERR  .01
extern struct coords *base;
int initial;
float last;

/**************TREE*FUNCTIONS********************/
int init23(char *file);
struct node *avail23(void);
void indent23(int h);
void print_tree23(struct node *node, int h);
int height23(struct node *node);
void free23(struct node *p);
int valid23(struct node *node);
float min23(struct node *node);
struct node *locatemin23(struct node *node);
float max23(struct node *node);
struct node *locatemax23(struct node *node);
int ckorder23(struct node *node);
int ckdepth23(struct node *node, int h);
int ckindex23(struct node *node);
struct node *search23(float x, struct node *node);
struct node *insert23(struct node **root, struct coords *new);
struct node *addson(struct coords *new, struct node *node, struct node **split, float *low);
void delete23(struct node **tree, float x);
int delete1(struct node *node, float x);

/************MATH*FUNCTIONS*********************/
float calcdist(struct coords *new);
