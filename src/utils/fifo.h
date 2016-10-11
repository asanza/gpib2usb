#ifndef fifo_H
#define fifo_H

typedef struct {
	char * buf;
	int head;
	int tail;
	int size;
} fifo_t;


int fifo_read(fifo_t* f, void* buf, int nbytes);
int fifo_write(fifo_t* f, const void* buf, int nbytes);
void fifo_init(fifo_t* f, char* buf, int size);

#endif // fifo_H
