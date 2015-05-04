struct dlist{
  int sz;
  int maxsz;
  char line[1];
};

#define INITSZ   100
#define INCRSZ   100
#define DLISTSZ(n)   ((size_t)sizeof(struct dlist) + ((n)-1)*sizeof(char))

struct dlist *init_dlist(void);
int ins_dlist(char*str, struct dlist **p);
void debug_dlist(struct dlist *p);
void prt_dlist(struct dlist *p);
