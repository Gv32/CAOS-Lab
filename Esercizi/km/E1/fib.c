#include "fib.h"
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

void fib(int n){
    static int a = 0;
    static int b = 1;
    static int sum = 0;
    for (int i = 0;i<n;i++){
        pr_info("%d %d\n", a, b);
        sum = a + b;
        a = b;
        b = sum;
    }
}