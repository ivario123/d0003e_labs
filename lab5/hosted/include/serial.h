#ifndef SERIAL_H
#define SERIAL_H

#include <unistd.h>
#include <fcntl.h> 
#include <errno.h>
#include <termios.h> 
#include "API.h"



int open_port(void);
int write_data(int file_desc);
int read_bit(int file_desc);
int exit_port(int file_desc);

#endif