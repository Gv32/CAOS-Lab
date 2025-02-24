#include <linux/kernel.h>
#include <linux/module.h>
#include "fib.h"
MODULE_LICENSE("GPL");

static int n = 0;

module_param(n, int, 0644);
MODULE_PARM_DESC(n, "number of iteration");

static int __init e_init(void){
    fib(n);
    return 0;
}

module_init(e_init);
