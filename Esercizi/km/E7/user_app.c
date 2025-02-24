#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define NAME "e7"
#define DEVICE_PATH "/dev/"NAME

int main(){
    int fd;
    fd = open(DEVICE_PATH, O_RDWR);

    if(fd < 0){
        printf("Error during opening file\n");
        return 1;
    }

    char strng1[5] = "";

    write(fd,"6",0);
    read(fd,strng1,0);

    printf("Value: %s\n",strng1);
    char strng2[5] = "";

    write(fd,"1",0);
    read(fd,strng2,0);

    printf("Value: %s\n",strng2);

}