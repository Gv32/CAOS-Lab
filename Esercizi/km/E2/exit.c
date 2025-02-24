#include <linux/kernel.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");


static void __exit e_exit(void){
    pr_info("Bye\n");
}

module_exit(e_exit);