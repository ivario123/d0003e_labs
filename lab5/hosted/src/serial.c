#include "serial.h"


const char* serial_port = "/dev/ttyACM0";
#define baud_rate 9600

struct termios control_field;
int open_port(void){

    // Define a file descriptor
    int file_desc;
    // Open the current port 
    printf("%s",serial_port);
    file_desc = open(serial_port, O_RDWR);
    // Handle no such port
    if(file_desc  == -1){
        return -1;
    }
    // Dissabeling parity bits
    control_field.c_cflag &= ~PARENB;
    // Setting to one stop bit
    control_field.c_cflag &= ~CSTOPB;
    // 8 bits per byte, no strange stuff
    control_field.c_cflag |= CS8;
    // Want to remove flow control but can't
    //control_field.c_cflag &= ~CRTSCTS;
    // Allowing us to read data  
    control_field.c_cflag |= CREAD ;
    // Removing limitation of newlines
    control_field.c_lflag &= ~ICANON;
    // Remove echo bits
    control_field.c_lflag &= ~ECHO;
    control_field.c_lflag &= ~ECHOE;
    control_field.c_lflag &= ~ECHONL;
    // Remove interrupt messages and such
    control_field.c_lflag &= ~ISIG;
    // dissable flow control
    control_field.c_iflag &= ~(IXON | IXOFF | IXANY);
    // remove all input modification of the data
    control_field.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    if (tcsetattr(file_desc, TCSANOW, &control_field) != 0) {  
        return -2;
    }

    return file_desc;
}
int write_data(int file_desc){
    unsigned char msg[] = { 'H', 'e', 'l', 'l', 'o', '\r' };
    printf("\n%d : ",'H');
    write(file_desc, msg, sizeof(msg));
}
int read_bit(int file_desc){
    char read_buf [256];

    
    int n = read(file_desc, &read_buf, sizeof(read_buf));
    printf("%d\n",read_buf[0]);
}
int exit_port(int file_desc){
    close(file_desc);

}