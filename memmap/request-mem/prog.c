#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/ioport.h>

// cat /proc/iomem shows this reguion is already reserved
// 00000000-00000000 : Reserved
#define MY_BASEADDRESS 0x00000000
#define MY_BASEADDRESS 0xf8000000
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
	}
	return 0;
}

static void mem_req_exit(void)
{
	release_mem_region(MY_BASEADDRESS, LENGTH);
}

module_init(mem_req_init);
module_exit(mem_req_exit);
