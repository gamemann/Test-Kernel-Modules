#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Deacon");
MODULE_DESCRIPTION("My first kernel module.");
MODULE_VERSION("0.1");

static int __init test_init(void)
{
    printk(KERN_INFO "The module has been initiated!");
    
    return 0;
}

static void __exit test_exit(void)
{
    printk(KERN_INFO "The module has exited!");
}

module_init(test_init);
module_exit(test_exit);