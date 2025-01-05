/*
* hello-5.c - Demonstrates command line argument passing to a module.
*/
#include <linux/init.h>
#include <linux/kernel.h> /* for ARRAY_SIZE() */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/stat.h>
MODULE_LICENSE("GPL");
static char *mystring = "Nobody";


module_param(mystring, charp, 0644);
MODULE_PARM_DESC(mystring,"Name of the user\n");




static int __init e1_init(void)
{

    pr_info("Greetings: %s\n", mystring);
    return 0;
}

static void __exit e1_exit(void)
{
    pr_info("Goodbye: %s\n", mystring);
}

module_init(e1_init);
module_exit(e1_exit);