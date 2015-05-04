/*
 *  fifo.h
 *
 */

struct fifo{
  int head;
  int tail;
  int sz;
  int maxsz;
  int data[1];
};

#define INITFIFOSZ    10000 
#define INCRFIFOSZ    10000
#define FIFOSZ(n)     (sizeof(struct fifo) + ((n)-1)*sizeof(int))

void print_fifo(struct fifo *f);
struct fifo *init_fifo(int num);
int insert_fifo(int x, struct fifo **f);
int extract_fifo(int *x, struct fifo *f);

