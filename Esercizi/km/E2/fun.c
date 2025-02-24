#include "fun.h"
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

void funz(char *vet1, char *vet2, int *intvet){
    int tmp = intvet[0]+intvet[1]+2;
    char stringa[tmp];
    int index = 0;
    for(int i = 0;i<intvet[0]+1;i++){
        stringa[index] = vet1[i];
        index++;
    }
    for(int i = 0;i<intvet[1]+1;i++){
        stringa[index] = vet2[i];
        index++;
    }    
    pr_info("%s\n",stringa);

}