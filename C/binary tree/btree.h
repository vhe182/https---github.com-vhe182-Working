struct node{
  int item;
  struct node *left;
  struct node *right;
};

struct node *ins_tree(int data, struct node **t);
void free_tree(struct node *t);
int reverse(struct node *t);
int p_reverse(struct node *t, int h);
int height(struct node *t);
int width(struct node *t);
int p_width(struct node *t, int l);
void print_tree(struct node *t);
void p_tree(struct node *t, int h);
