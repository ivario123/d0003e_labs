/*
 *
 * tinythreads.h
 *
 */

#ifndef _TINYTHREADS_H
#define _TINYTHREADS_H
#include <stdint-gcc.h>
#define TIMER_SCALING_1024 0b101
#define TIMER_SCALING_256  0b100
#define TIMER_SCALING_64   0b011
#define TIMER_SCALING_8    0b010
#define TIMER_SCALING_1    0b001
#define TIMER_STOP		   0b000

struct thread_block;
typedef struct thread_block *thread;
void spawn_no_arg(void (*function)(void));
void spawn(void (*code)(int), int arg);
void yield(void);


struct mutex_block {
    int locked;
    thread waitQ;
};
typedef struct mutex_block mutex;

#define MUTEX_INIT {0,0}
void lock(mutex *m);
void unlock(mutex *m);
uint16_t get_timer_int_counter();
void reset_timer_int_counter();
#endif

