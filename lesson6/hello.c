#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/io.h>

// Use this first line to see a failure case
//#define MY_BASEPORT 0x0070
// Why? Because 70 is already used by rtc0
// sudo cat /proc/ioports
//  0000-0cf7 : PCI Bus 0000:00
//  0000-001f : dma1
//  0020-0021 : PNP0001:00
//  0020-0021 : pic1
//  0040-0043 : timer0
//  0050-0053 : timer1
//  0060-0060 : keyboard
//  0061-0061 : PNP0800:00                 -- space after this for base port 62
//  0064-0064 : keyboard
//  0070-0071 : rtc0                       -- rtc0 uses 70 here
//  0080-008f : dma page reg

// At work, this was free, but at home in was PNP0C09
// sudo cat /proc/ioports
//#define MY_BASEPORT 0x0062
#define MY_BASEPORT 0x0068
#define NUMBER_PORTS 2

MODULE_LICENSE("GPL");

static int mod_init(void)
{
	printk(KERN_INFO "lesson 6 module init");

	if (!request_region(MY_BASEPORT, NUMBER_PORTS, "myports")) 
	{
		pr_info("request region failed for myports\n");
		return -1;
	} 
	else 
	{
		pr_info("request region success for myports\n");
		outb(0xa, MY_BASEPORT);
	}
	return 0;
}

static void mod_exit(void)
{
	unsigned int a;
	a = inb(MY_BASEPORT);
	pr_info("Value at %02x is %02x\n", MY_BASEPORT, a);
	release_region(MY_BASEPORT, NUMBER_PORTS);
	return;
}

module_init(mod_init);
module_exit(mod_exit);

