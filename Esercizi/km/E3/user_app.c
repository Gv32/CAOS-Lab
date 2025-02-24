#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define NAME "led"
#define DEVICE_PATH "/dev/"NAME

int main(){
    int fd;
    fd = open(DEVICE_PATH,O_RDWR);

    if(fd < 0){
        printf("Error during opening file\n");
    }

    char intervallo[5] = "1000";
    char strng1[5];
    strcpy(intervallo,"1000");

    write(fd,intervallo,5);

    read(fd,strng1,5);

    printf("Value: %s\n",strng1);

}