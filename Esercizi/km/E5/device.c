#include <linux/atomic.h> 
#include <linux/cdev.h> 
#include <linux/delay.h> 
#include <linux/device.h> 
#include <linux/fs.h> 
#include <linux/init.h> 
#include <linux/kernel.h>
#include <linux/module.h> 
#include <linux/printk.h> 
#include <linux/types.h> 
#include <linux/uaccess.h>
#include <linux/version.h> 
#include <linux/string.h>
 
#include <asm/errno.h> 
#include "shared.h"

 
static int device_open(struct inode *, struct file *); 
static int device_release(struct inode *, struct file *); 
static ssize_t device_read(struct file *, char __user *, size_t, loff_t *); 
static ssize_t device_write(struct file *, const char __user *, size_t, 
                            loff_t *);
static long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned
		long ioctl_param);
 
#define SUCCESS 0 
#define DEVICE_NAME "es5"
#define BUF_LEN 80
 
int vetI[20];
int index = 0;

static int major;
 
enum { 
    CDEV_NOT_USED, 
    CDEV_EXCLUSIVE_OPEN, 
}; 
  
static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED); 
 
static char msg[BUF_LEN + 1];
 
static struct class *cls; 
 
static struct file_operations device_fops = { 
    .read = device_read, 
    .write = device_write, 
    .open = device_open, 
    .release = device_release,
    .unlocked_ioctl = device_ioctl,
}; 
 
static int __init device_init(void) 
{ 
    major = register_chrdev(0, DEVICE_NAME, &device_fops); 
 
    if (major < 0) { 
        pr_alert("Registering char device failed with %d\n", major); 
        return major; 
    } 
 
    pr_info("I was assigned major number %d.\n", major); 


#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0) 
    cls = class_create(DEVICE_NAME); 
#else 
    cls = class_create(THIS_MODULE, DEVICE_NAME); 
#endif

    device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME); 
 
    pr_info("Device created on /dev/%s\n", DEVICE_NAME); 
 
    return SUCCESS; 
} 
 
static void __exit device_exit(void) 
{ 
    device_destroy(cls, MKDEV(major, 0)); 
    class_destroy(cls); 
 
    unregister_chrdev(major, DEVICE_NAME); 
} 
 
static int device_open(struct inode *inode, struct file *file) 
{ 
    static int counter = 0; 

    if (atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN)) 
        return -EBUSY; 
 
    sprintf(msg, "I already told you %d times Hello world!\n", counter++); 

    try_module_get(THIS_MODULE); 
 
    return SUCCESS; 
} 
 
static int device_release(struct inode *inode, struct file *file) 
{ 
    atomic_set(&already_open, CDEV_NOT_USED); 
 
    module_put(THIS_MODULE); 
 
    return SUCCESS; 
} 
 

static ssize_t device_read(struct file *filp, 
                           char __user *buffer,
                           size_t length,
                           loff_t *offset
			   ) 
{ 
    int bytes_read = 0;
    char stringa[index*2];
    array_to_string(vetI,index,stringa);
    int i = 0;
    while(stringa[i] != '\0'){
        put_user(stringa[i], buffer + i);
        bytes_read++;
        i++;
    }
    put_user('\0',buffer + i);
    return bytes_read; 
} 
 
static ssize_t device_write(struct file *filp, const char __user *buff, 
                            size_t len, loff_t *off) 
{ 
    int byte_write = 0;
    char stringa[len];
    int vetInt[len/2];

    for(int i = 0 ; i < len; i++){
        get_user(stringa[i], buff + i);
        byte_write++;
    }
    
    string_to_array(stringa,vetInt,len/2);

    for(int i=0;i<len/2;i++){
        vetI[index] = vetInt[i];
        index++;
    }

    return byte_write; 
} 

static long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned
		long ioctl_param){ 
 
    switch (ioctl_num) { 

		case 0:
            char msg[4];
            sprintf(msg,"%d\n",index);
            strcpy(ioctl_param,msg);
			break; 

		case 1: 
            index = 0;
            break;


    } 
 
    atomic_set(&already_open, CDEV_NOT_USED); 
 
    return SUCCESS; 
}
 
module_init(device_init); 
module_exit(device_exit); 
 
MODULE_LICENSE("GPL");
