#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>

typedef struct node_t {
	int size;
	struct node_t* next;
} free_list_node;

typedef struct malloc_header {
	int size;
	int magic;   //not needed for current code
} mheader;

static void* mem = NULL;
static int* blocks = NULL;
static int* cur_size = NULL;

static free_list_node* head = NULL;

// Implement these yourself
int my_init(){	

	mem = mmap(NULL, 4096, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1,0);
	if(mem == MAP_FAILED) {
		// printf("Error occurred %s\n", strerror(errno));
		return errno;
	}
	blocks = (int*) mem;
	*blocks = 0;
	cur_size = (int*)((char*)blocks + (int)sizeof(int));
	head = (free_list_node*) ((char*)cur_size + (int)sizeof(int));
	head->size = 4096 - (int)sizeof(free_list_node) - 2*(int)sizeof(int);
	head->next = NULL;
	*cur_size = (int)sizeof(free_list_node);

	return 0;
}

void* my_alloc(int count){
	free_list_node* curblk = NULL;
	free_list_node* prevblk = NULL;
	free_list_node* prev = NULL;
	free_list_node* bestfitblk = NULL;

	if (count <= 0 || count%8 != 0) {
		// fprintf(stderr, "Error: Incorrect memory size\n");
		return NULL;
	}

	if(head == NULL) {
		// fprintf(stderr, "Error: Memory not initialized using my_init()\n");
		return NULL;
	}

	//best fit block first strategy
	curblk = head;
	while(curblk != NULL) {
		if( (curblk->size + (int)sizeof(free_list_node)) >= (count + (int)sizeof(mheader))) {
			if(bestfitblk == NULL) {
				bestfitblk = curblk;
				prev = prevblk;
			}
			else if (bestfitblk->size > curblk->size){
				bestfitblk = curblk;
				prev = prevblk;
			}
		}
		prevblk = curblk;
		curblk = curblk->next;
	}

	if(bestfitblk == NULL) {
		// fprintf(stderr, "Error: Memory cannot be allocated\n");
		return NULL;
	} 

	mheader* mhead;
	int size = bestfitblk->size;

	if (size >= count + (int)sizeof(mheader)) {
		free_list_node* splitblk;
		splitblk = (free_list_node*)((char*)bestfitblk + count + (int)sizeof(mheader));
		splitblk->next = bestfitblk->next;
		splitblk->size = size - count - (int)sizeof(mheader);

		mhead = (mheader* )(bestfitblk);
		mhead->size = count;
		mhead = (mheader*)((char*)mhead + (int)sizeof(mheader));

		if(prev != NULL)
			prev->next = splitblk;
		else
			head = splitblk;
		*cur_size += ((int)sizeof(mheader) + count);
	}

	else {
		int extra = size + (int)sizeof(free_list_node) - count - (int)sizeof(mheader);
		if(prev != NULL)
			prev->next = bestfitblk->next;
		else
			head = bestfitblk->next;

		count += extra;
		mhead = (mheader* )(bestfitblk);
		mhead->size = count;
		mhead = (mheader*)((char*)mhead + (int)sizeof(mheader));
		*cur_size += ((int)sizeof(mheader) + count);
		*cur_size -= (int)sizeof(free_list_node);
	}

	*blocks += 1;
	return (void*) mhead;
}

void my_free(void *ptr){
	if(ptr == NULL)
		return;

	mheader* hptr = (mheader*)((char*) ptr - (int)sizeof(mheader));
	free_list_node* freeblk = (free_list_node*) hptr;
	
	int count = hptr->size;

	free_list_node* curblk = head;
	free_list_node* prevblk = NULL;
	free_list_node* nextblk = NULL;
	int npos = 0, ppos = 0;
	int t = 0;

	while(curblk != NULL) {
		if((free_list_node*)((char*)curblk + curblk->size + (int)sizeof(free_list_node)) == freeblk) {
			prevblk = curblk;
			ppos = t;
		}
		if((free_list_node*)((char*)freeblk + count + (int)sizeof(mheader)) == curblk) {
			nextblk = curblk;
			npos = t;
		}
		t++;
		curblk = curblk->next;
		// printf("H1\n");
	}

	int p,n;

	if(prevblk == NULL && nextblk == NULL) {
		//no coalescing possible
		// printf("H2\n");
		freeblk->size = count + (int)sizeof(mheader) - (int)sizeof(free_list_node);
		freeblk->next = head;
		head = freeblk;
		*cur_size -= ((int)sizeof(mheader) + count);
		*cur_size += (int)sizeof(free_list_node);
	}

	if(prevblk != NULL && nextblk == NULL) {
		p = prevblk->size;
		// printf("H3\n");
		prevblk->size += (count + (int)sizeof(mheader));
		*cur_size -= ((int)sizeof(mheader) + count);

	}

	if(nextblk != NULL && prevblk == NULL) {
		n = nextblk->size;
		freeblk->next = nextblk->next;
		freeblk->size = count + (int)sizeof(mheader) + n;
		if(nextblk == head) {
			// printf("Here\n");
			head = freeblk;
			*cur_size -= ((int)sizeof(mheader) + count);
		}
		//change previous pointer
		else {
			// printf("Here2\n");
			curblk = head;
			free_list_node* prev = NULL;
			while(curblk != nextblk) {
				prev = curblk;
				curblk = curblk->next;
			}
			prev->next = freeblk;	
			*cur_size -= ((int)sizeof(mheader) + count);
		}
	}

	if(nextblk != NULL && prevblk != NULL) {
		n = nextblk->size;
		p = prevblk->size;
		if(ppos < npos) {
			// printf("H4_1\n");
			prevblk->next = nextblk->next;
			prevblk->size += (count + (int)sizeof(mheader) + (int)sizeof(free_list_node) + n);
		}
		else {
			// printf("H4_2\n");
			free_list_node* temp = prevblk->next;

			if (nextblk == head) {
				// printf("H4_2_1\n");
				nextblk = prevblk;
				n += (count + (int)sizeof(mheader) + (int)sizeof(free_list_node) + p);
				nextblk->size = n;
				nextblk->next = temp;
				head = nextblk;
			}
			else {
				// printf("H4_2_2\n");
				curblk = head;
				free_list_node* prev = NULL;
				while(curblk != nextblk) {
					prev = curblk;
					curblk = curblk->next;
				}
				nextblk = prevblk;
				n += (count + (int)sizeof(mheader) + (int)sizeof(free_list_node) + p);
				nextblk->size = n;
				nextblk->next = temp;
				prev->next = nextblk;
			}

			//store pointer addresses.
		}
		*cur_size -= ((int)sizeof(mheader) + count + (int)sizeof(free_list_node));
	}
	*blocks -= 1;
	return;
}

void my_clean(){
	int r = munmap(mem, 4096);
	if(r != 0){
		// printf("Error occurred \n");
		// fprintf(stderr, strerror(errno));
		return;
	}	
	// printf("Memory has been deallocated\n");
	return;
}

void my_heapinfo(){
	if(head == NULL && blocks == NULL)
		return;
	int a, b, c, d, e, f;
	int r = 0;
	d = *blocks;
	b = *cur_size;
	a = 4096 - 2*(int)sizeof(int);
	c = a - b;
	e = 5000;
	f = -1;
	free_list_node* curblk = head;
	while(curblk != NULL) {
		if(curblk->size > f) {
			f = curblk->size;
		}
		if(curblk->size < e && curblk->size != 0) {
			e = curblk->size;
		}
		curblk = curblk->next;
		r++;
	}
	if (e == 5000) 
		e = 0;
	if(f == -1)
		f = 0;

	printf("Blocks in free list: %d\n", r);
	// Do not edit below output format
	printf("=== Heap Info ================\n");
	printf("Max Size: %d\n", a);
	printf("Current Size: %d\n", b);
	printf("Free Memory: %d\n", c);
	printf("Blocks allocated: %d\n", d);
	printf("Smallest available chunk: %d\n", e);
	printf("Largest available chunk: %d\n", f);
	printf("==============================\n");
	// Do not edit above output format
	return;
}