#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/delay.h>
#include <linux/io.h>


#define RTC_ADDRESS     0x70
#define RTC_DATA        0x71

#define SECONDS         0x00
#define MINUTES         0x02
#define HOURS           0x04
#define DAY_WEEK        0x06
#define DAY_MONTH       0x07
#define MONTH           0x08
#define YEAR            0x09


#define REGA            0x0A
#define REGB            0x0B
#define REGC            0x0C
#define REGD            0x0D 

unsigned char rtc_read(unsigned char address)
{
	// write the address of the register, then read it
	outb_p(address, RTC_ADDRESS);
	return inb_p(RTC_DATA);
}

void rtc_write(unsigned char address, unsigned char value)
{
	outb_p(address, RTC_ADDRESS);
	outb_p(value, RTC_DATA);
}
int __init  rtc_drv_init(void)
{
	unsigned char regb = rtc_read(REGB);
	pr_info("register B:%02x\n", regb);
	if(regb & 0x01)
	{
		pr_info("daylight saving enabled\n");
	}
	else
	{
		pr_info("daylight saving disabled\n");
	}

	if(regb & 0x02)
	{
		pr_info("24 hour mode\n");
	}
	else
	{		
		pr_info("12 hour mode\n");
	}

	if(regb & 0x04)
	{
		pr_info("Data in Binary format\n");
	}
	else
	{
		pr_info("Data in BCD format\n");
	}

	pr_info("Hours:%02x\t Minutes:%02x\t Seconds:%02x\n",
	rtc_read(HOURS), rtc_read(MINUTES), rtc_read(SECONDS));
	
	// This section actually updates the RTC
	// sudo hwclock --debug
	// This command before and after shows the changes to the RTC
	rtc_write(HOURS, 3);	
	rtc_write(MINUTES, 10);
	rtc_write(SECONDS, 2);
	pr_info("Hours:%02x\t Minutes:%02x\t Seconds:%02x\n",
		rtc_read(HOURS), rtc_read(MINUTES), rtc_read(SECONDS));

	return 0;
}

void  __exit rtc_drv_exit(void)
{

}

MODULE_LICENSE("GPL");
module_init(rtc_drv_init);
module_exit(rtc_drv_exit);
