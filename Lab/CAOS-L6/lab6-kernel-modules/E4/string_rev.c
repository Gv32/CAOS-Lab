#include "string_rev.h"
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

void rev_string(char *stringa,int n){
    for (int i = n-1;i>=0;i--){
        pr_info("%c\n",stringa[i]);
    }
}

