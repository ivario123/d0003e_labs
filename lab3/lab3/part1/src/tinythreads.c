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
// Global counter, this one works
uint16_t timer_int_counter = 0;
// A pointer to TCINT register
volatile uint16_t * timer = (uint16_t *)0x84;
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
// All of the modifications are commented and should not affect the results
static void initialize(void) {
	// Setting a pointer to timer 1 reg
	volatile uint16_t * timer = (uint16_t *)0x84;
	
	// Setting power options
	CLKPR = 0x80;
	CLKPR = 0X00;
	
	// Setting the pre-scaling factor to 256
	TCCR1B = TCCR1B | TIMER_SCALING_1024;
	
	// Setting the pull up
	PORTB = PORTB   | (1<<7);
	
	// Enabling interrupts
	MCUSR = MCUSR   | 1<<7;
	EICRA = EICRA   | 3;
	// Button int
	//EIMSK = EIMSK   | 1<<7 | 1;
	//PCMSK1 = PCMSK1 | 1<<7;
	
	// Setting timer int enabled
	TIMSK1 = TIMSK1|2;
	
	
	// Specifying the target interrupt period
	uint16_t * target_time = (uint16_t *)0x88;
	*target_time = 391;												// Approximate form of 50ms in clock cycles * 1024
	
	
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

	// reseting timer
	*timer = 0;

    initialized = 1;
}

// From the basic lib
static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
            q = q->next;
        q->next = p;
    }
}
// From the basic lib
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

// From the basic lib
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

    enqueue(newp, &readyQ);
    ENABLE();
}

// Enques current thread and starts the next thread in line
void yield(void) {
	DISABLE();
	// Pluck the first thread from the queue
	// Enqueue the thread that was plucked
	enqueue(current,&readyQ);
	// Dequeue and execute next thread
	dispatch(dequeue(&readyQ));
	ENABLE();
}


// Increments a timer counter and the resets the timer it self.
ISR(TIMER1_COMPA_vect){
	DISABLE();
	timer_int_counter++;
	*timer = 0;
	ENABLE();
	yield();
}
// same as in part 1
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

// same as in part 1
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
// Not disabeling the interrupts since this will be inlined by any optimizing compiler
uint16_t get_timer_int_counter(){
	return timer_int_counter;
}
// Not disabeling the interrupts since this will be inlined by any optimizing compiler
void reset_timer_int_counter(){
	DISABLE();
	timer_int_counter = 0;
	ENABLE();
}

