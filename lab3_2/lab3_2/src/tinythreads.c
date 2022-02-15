#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/tinythreads.h"

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
                        *((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4
uint16_t timer_int_counter = 0;
struct thread_block {
	void (*function)(int);   // code to run
	int arg;                 // argument to the above
	thread next;             // for use in linked lists
	jmp_buf context;         // machine state
	char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];

struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;

static void initialize(void) {
	
	// Setting power options
	CLKPR = 0x80;
	CLKPR = 0X00;
	
	// Setting the pre-scaling factor to 1024
	TCCR1B = TCCR1B | TIMER_SCALING_1024;
	
	// Setting the pull up
	PORTB = PORTB   | (1<<7);
	
	// Enabling interrupts
	MCUSR = MCUSR   | 1<<7;
	EICRA = EICRA   | 3;
	
	EIMSK = EIMSK   | 1<<7 | 1;
	PCMSK1 = PCMSK1 | 1<<7;
	
	// Setting timer int enabled
	TIMSK1 = TIMSK1|2;
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

	

    initialized = 1;
	ENABLE();
}

static void enqueue(thread p, thread *queue) {
	thread q = *queue;
	*queue = p;
	
	(*queue)->next = q;
}

static thread dequeue(thread *queue) {
	thread p = *queue;
	if (*queue) {
		*queue = (*queue)->next;
	} else {
		// Empty queue, kernel panic!!!
		while (1) ;  // not much else to do...
	}
	return p;
}

static void dispatch(thread next) {
	if (setjmp(current->context) == 0) {
		current = next;
		longjmp(next->context,1);
	}
}

void spawn(void (* function)(int), int arg) {
	
	thread newp;

	DISABLE();
	if (!initialized) initialize();
	enqueue(current,&readyQ);
	newp = dequeue(&freeQ);
	newp->function = function;
	newp->arg = arg;
	newp->next = NULL;
	if (setjmp(newp->context) == 1) {
		ENABLE();
		current->function(current->arg);
		DISABLE();
		enqueue(current, &freeQ);
		dispatch(dequeue(&readyQ));
	}
	SETSTACK(&newp->context, &newp->stack);
	//enqueue(newp, &readyQ);
	ENABLE();
	dispatch(newp);
}

void yield(void) {
	DISABLE();
	// Pluck the first thread from the queue
	// Enqueue the thread that was plucked
	enqueue(current,&readyQ);
	// Dequeue and execute next thread
	dispatch(dequeue(&readyQ));
	ENABLE();
}

void lock(mutex *m) {
	DISABLE();
	if(m->locked==0){
		// Mutex is free, just lock and return
		m->locked = 1;
	}
	else{
		// Mutex is not free, wait until it is free
		enqueue(current,&(m->waitQ));
		dispatch(dequeue(&readyQ));
	}	
	ENABLE();
}

void unlock(mutex *m) {
	DISABLE();
	if(m->locked!=0){
		enqueue(current,&readyQ);
		if(m->waitQ!=NULL){
			dispatch(dequeue(&(m->waitQ)));
		}
		else{
			m->locked = 0;
			dispatch(dequeue(&readyQ));
		}
	}
	ENABLE();
}



