#include <linux/kernel.h>
#include <linux/module.h>
#include "funz.h"
MODULE_LICENSE("GPL");

static char *stringa = "Hello";
static int n = 5;
static int myintarray[5] = {0,0,0,0,0};
static int arr_argc;

module_param(n, int, 0644);
MODULE_PARM_DESC(n, "strlen");
module_param(stringa, charp, 0644);
module_param_array(myintarray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintarray, "An array of integers");

static int __init e_init(void){
    int v = 0;
    for(int i = 0; i<n;i++){
        if(myintarray[i]!=0){
            v++;
        }
    }
    fun(myintarray,stringa,n);
    return 0;
}

module_init(e_init);