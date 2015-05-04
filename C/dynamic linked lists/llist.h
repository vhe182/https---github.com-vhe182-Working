struct lnode{
  int index;
  struct lnode *next;
  struct lnode *prev;
};
struct llist{
  struct lnode *head;
  struct lnode *tail;
};

struct llist *init_llist();
struct lnode *ins_llist(char *str, struct llist *l);
int del_llist(int num, struct llist *l);
void prt_llist(struct llist *l);
void free_llist(struct llist *l);
int valid_llist(struct llist *l);
static struct dlist *c;
