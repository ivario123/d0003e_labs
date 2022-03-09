#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "serial.h"

#define interface_south 's'
#define interface_north 'n'
#define interface_exit 'e'

long south,north,middle;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
void *handle_queues(void * arg){
    south = 0;
    north = 0;
    middle = 0;
    while(1){
        char *line = NULL;
        size_t len = 0;
        size_t lineSize = 0;
        lineSize = getline(&line, &len, stdin);
        pthread_mutex_lock(&queue_mutex);
        switch(*line)
        {
        case 'n':
            north +=1;
            break;
        case 's':
            south +=1;
            break;
        case 'e':
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Incorrect command");
            continue;
            break;
        }
        printf("\033[A\33[2K");
        printf("Command : %c, North : %d, South : %d, Driving : %d\nNew command : ",*line,north,south,middle);
        pthread_mutex_unlock(&queue_mutex);
        free(line);
    }

}
void *handle_garbage(void * arg){
    __uint32_t itter = 0;
    while(1){
        if(itter == 0)
            printf("Garbage\n");
        itter++;
    }
}

int main(int args[]){
    printf("Hey, welcome to the simulator!\nPress : '%c' to enqueue in north direction\nPress : '%c' to enqueue in south direction\nPress : '%c' to exit\n=================================\n",interface_north,interface_south,interface_exit);
    pthread_t console_thread,garbage;
    int port = open_port();
    printf("open port returned : %d",port);
    write_data(port);
    read_bit(port);
    exit_port(port);

    pthread_create(&console_thread,NULL,&handle_queues,NULL);
    pthread_create(&garbage,NULL,&handle_garbage,NULL);
    pthread_join(console_thread,NULL);
    pthread_join(garbage,NULL);
    
}