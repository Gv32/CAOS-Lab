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
static int n = 10;
static int flag = 1;


module_param(n, int, 0444);
MODULE_PARM_DESC(n, "N for the for");
module_param(flag, int, 0444);
MODULE_PARM_DESC(flag, "Number selected by the user");

static int __init e2_init(void)
{
    for (int i = 0; i < n;i++){
        pr_info("N%d: %d\n", i,flag);
        msleep(1000);
    }
    return 0;
}

static void __exit e2_exit(void)
{
    pr_info("Goodbye");
}

module_init(e2_init);
module_exit(e2_exit);