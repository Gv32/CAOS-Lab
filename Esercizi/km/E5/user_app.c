#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "shared.h"

#define NAME "es5"
#define DEVICE_PATH "/dev/"NAME

int main(){
    int fd;
    fd = open(DEVICE_PATH,O_RDWR);
    int svet = 3;
    int vet1[svet];
    for(int i = 0;i<svet;i++){
        vet1[i]=i;
    }
    int vet2[svet];
    for(int i = 0;i<svet;i++){
        vet2[i]=i;
    }
    char str1[svet*2];
    char str2[svet*2];
    char str3[svet*2 + svet*2];
    if(fd < 0){
        printf("Error during opening file\n");
        return -1;
    }
    array_to_string(vet1,svet,str1);
    array_to_string(vet2,svet,str2);
    
    write(fd,str1,strlen(str1)+1);
    write(fd,str2,strlen(str2)+1);
    read(fd,str3,svet*2+svet*2);
    printf("%s\n",str3);
    char message[4];
    ioctl(fd,0,message);
    printf("%s\n",message);
    

}