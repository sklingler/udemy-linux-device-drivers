#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

// Seems to be different on other installs
// I was never able to get the static effect he got
#define SPEAKER_PORT 0x62

static int speaker_mod_init(void)
{
        printk(KERN_INFO "speaker module init");
        outb(0x03, SPEAKER_PORT); // Enabling speaker
        ssleep(5);
        outb(0x00, SPEAKER_PORT); // Disabling Speaker
        printk(KERN_INFO "end of speake module init");
        return 0;
}

static void speaker_mod_exit(void)
{
        printk(KERN_INFO "speaker mod exit");
}

module_init(speaker_mod_init);
module_exit(speaker_mod_exit);
