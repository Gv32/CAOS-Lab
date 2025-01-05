/*
* hello-5.c - Demonstrates command line argument passing to a module.
*/
#include <linux/init.h>
#include <linux/kernel.h> /* for ARRAY_SIZE() */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/stat.h>
#include <linux/delay.h>
MODULE_LICENSE("GPL");
static int sum = 0;
static int n = 10;
static int myintarray[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int arr_argc = 0;


module_param(sum, int, 0444);
MODULE_PARM_DESC(n, "Counter for the sum");
module_param_array(myintarray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintarray, "An array of integers");

static int __init e3_init(void)
{
    pr_info("Welcome\n");
    for (int i = 0; i < n;i++){
        sum = sum + myintarray[i];
    }
    return 0;
}

static void __exit e3_exit(void)
{
    pr_info("Sum: %d\n",sum);
    pr_info("Bye\n");
}

module_init(e3_init);
module_exit(e3_exit);