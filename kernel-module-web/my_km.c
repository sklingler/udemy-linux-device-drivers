#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static int __init my_init(void)
{
   printk(KERN_INFO "Loading hello module...\n");
   printk(KERN_WARNING "Hello world\n");
   return 0;
}

static void __exit my_exit(void)
{
   printk(KERN_INFO "Goodbye from Hello world\n");
   return;
}

module_init(my_init);
module_exit(my_exit);