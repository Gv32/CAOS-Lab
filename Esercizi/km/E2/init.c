#include <linux/kernel.h>
#include <linux/module.h>
#include "fun.h"
MODULE_LICENSE("GPL");

static char *string1 = "A";
static char *string2 = "A";
static int n = 2;
static int myintarray[2] = { 0, 0};
static int arr_argc;

module_param(n, int, 0444);
MODULE_PARM_DESC(n, "intvet length");
module_param(string1, charp, 0644);
MODULE_PARM_DESC(myintarray, "An array of char");
module_param(string2, charp, 0644);
MODULE_PARM_DESC(myintarray, "An array of char");
module_param_array(myintarray, int, &arr_argc, 0644);
MODULE_PARM_DESC(myintarray, "An array of integers");

static int __init e_init(void){
    funz(string1,string2,myintarray);
    return 0;
}

module_init(e_init);