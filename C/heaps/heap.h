struct heap{
  int sz;
  int maxsz;
  int item [1];
};

#define INITHSZ  20
#define INCRHSZ  10
#define NIL      -1
/*
 *  r = index of node
 *  n = total elements in heap
 */
#define HLISTSZ(n)     ((size_t)(sizeof(struct heap) + ((((n)-1)*sizeof(int)))))

#define PARENT(r,n)    ( 0 < (r) && (r) < (n) ? ((r)-1)/2 : -1)
#define LEFT(r,n)     ( 2*(r)+1 < (n) ? 2*(r)+1 : -1 )
#define RIGHT(r,n)    ( 2*(r)+2 < (n) ? 2*(r)+2 : -1 )

// #define LEFTS(r,n)     ( ((r)-1) < ? (r)-1: -1 )
// #define RIGHTS(r,n)   

/*******DYNAMIC*LIST*FUNCTIONS***********/
struct heap *init_heap(int num);
int insert_heap(int num, struct heap **p);
void print_heap(struct heap *p);
void debug_heap(struct heap *p);

/***********HEAP*FUNCTIONS**************/
void build_heap(struct heap*);
void siftdown(struct heap*, int r);
void siftup(struct heap*, int r);
int valid_heap(struct heap*);
int rmmin_heap(struct heap*);
