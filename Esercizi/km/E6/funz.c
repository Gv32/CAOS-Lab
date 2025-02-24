#include "funz.h"
#include <linux/kernel.h>
#include <linux/module.h>

void fun(int *vet, char *stringa, int n){
    for(int i = 0 ; i < n ; i++){
        pr_info("%c\n",stringa[vet[i]]);
    }
}