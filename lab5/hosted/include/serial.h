#ifndef SERIAL_H
#define SERIAL_H

#include <unistd.h>
#include <fcntl.h> 
#include <errno.h>
#include <termios.h> 
#include "API.h"


int open_port(void);
int write_data(void * arg);
void * read_bit(void *arg);
int exit_port(void * arg);

#endif