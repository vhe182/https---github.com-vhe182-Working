struct dlist{
  int sz;
  int maxsz;
  char item [1][1024];
};

#define INITSZ  6
#define INCRSZ  9
#define BUFSZ   1024
#define DLISTSZ(n)  ((size_t)(sizeof(struct dlist) + (((n-1)*(BUFSZ))*sizeof(char))))

struct dlist *init_dlist(int num);
int ins_dlist(char *str, struct dlist **p);
void prt_dlist(struct dlist *p);
void debug_dlist(struct dlist *p);
