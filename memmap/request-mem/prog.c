#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/io.h>

// cat /proc/iomem shows this reguion is already reserved
// 00000000-00000000 : Reserved
// #define MY_BASEADDRESS 0x00000000
#define MY_BASEADDRESS 0xf8000000
// seanklingler@pop-os:~/code/udemy-device/memmap/request-mem$ sudo cat /proc/iomem  | grep myp
// f8000000-f800000e : myports
// This assignment goes away on rmmmod

#define LENGTH 0xf

MODULE_LICENSE("GPL");

static int mem_req_init(void)
{
	if (!request_mem_region(MY_BASEADDRESS, LENGTH, "myports"))
	{
		pr_info("request mem region failed for myports\n");
		return -1;
	}
	else
	{
		pr_info("request mem region success for myports\n");
		void __iomem *p;
		p = ioremap(MY_BASEADDRESS, LENGTH);
		pr_info("ioremap returned:%px\n", p);
		*(unsigned int *)p = 0x12345678;
		pr_info("read:%04x\n", *(unsigned int *)p);

		iowrite32(0x12345699, p);
		int value = ioread32(p);
		pr_info("value second read/write:%02x\n", value);

		iounmap(p);
	}
	return 0;
}

static void mem_req_exit(void)
{
	release_mem_region(MY_BASEADDRESS, LENGTH);
}

module_init(mem_req_init);
module_exit(mem_req_exit);
