#include <linux/kernel.h>
#include <linux/module.h>
#include "string_rev.h"
MODULE_LICENSE("GPL");

static char *string = "Hello";
static int n = 5;

module_param(n, int, 0644);
MODULE_PARM_DESC(n, "strlen");
module_param(string, charp, 0644);
MODULE_PARM_DESC(myintarray, "An array of char");

static int __init e4_init(void){
    rev_string(string,n);
    return 0;
}

module_init(e4_init);