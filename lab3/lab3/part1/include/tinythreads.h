/*
 *
 * tinythreads.h
 *
 */

#ifndef _TINYTHREADS_H
#define _TINYTHREADS_H

#define TIMER_SCALING_1024 5
#define TIMER_SCALING_256  4
#define TIMER_SCALING_64   3
#define TIMER_SCALING_8    2
#define TIMER_SCALING_1    1
#define TIMER_STOP		   0
#include "lcd_driver.h"

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

