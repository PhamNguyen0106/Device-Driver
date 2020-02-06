#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>
#include <linux/ioctl.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <linux/err.h>

#define AUTHOR "NguyenPham <dangnguyen0106@gmail.com>"

#define GPIO_ADDR_BASE				0x209C000
#define GPIO_SIZE					0x001801C
#define	GPIO_DR_OFFSET				0x00
#define GPIO_GDIR_OFFSET			0x04
#define GPIO_PSR_OFFSET				0x08
#define GPIO_ICR1_OFFSET			0x0C
#define GPIO_ICR2_OFFSET			0x10
#define GPIO_IMR_OFFSET 			0x14
#define GPIO_ISR__OFFSET			0x18
#define GPIO_EDGE_SEL_OFFSET		0x10

#define IOMUXC_ADDR_BASE			0x20E0000
#define IOMUXC_SIZE					0x094C
#define IOMUXC_DATA03_OFFSET		0x00
#define IOMUXC_DATA04_OFFSET		0x00
#define IOMUXC_DATA05_OFFSET		0x00
#define IOMUXC_DATA06_OFFSET		0x00
#define IOMUXC_DATA07_OFFSET		0x00

#define ATL5			(5<<0)

#define GPIO_21	 		21

#define OUTPUT   		1
#define INPUT 			0
#define HIGH			1
#define LOW				0

#define GPIO_SET_BIT(x)				(1 << x)
#define GPIO_CLEAR_BIT(x)			~(1 << x)
#define GPIO_CLEAR_DR				0

unsigned int __iomem *gpio_addr;
unsigned int __iomem *iomuxc_addr;

static void iomuxc_gpio_mode(int iomuxc_offset)
{
	iomuxc_offset /= 4;
	iomuxc_addr[iomuxc_offset] |= ATL5;
}

static void gpio_mode(int gpio, int mode)
{
	if(mode == INPUT)
	{
		printk("gpio_%d INPUT\n",gpio);
		gpio_addr[GPIO_GDIR_OFFSET/4] &= GPIO_CLEAR_BIT(gpio);
	}
	else if(mode == OUTPUT)
	{
		printk("gpio_%d OUTPUT\n",gpio);
		gpio_addr[GPIO_GDIR_OFFSET/4] |= GPIO_SET_BIT(gpio);
	}
}

static void gpio_write(int gpio, int level)
{
	if(level == HIGH)
	{
		printk("gpio_%d HIGH\n",gpio);
		gpio_addr[GPIO_DR_OFFSET/4] |= GPIO_SET_BIT(gpio);
	}
	else if (level == LOW)
	{
		printk("gpio_%d LOW\n",gpio);
		gpio_addr[GPIO_DR_OFFSET/4] &= GPIO_CLEAR_BIT(gpio);
	}
}

static int __init led_init(void)
{
	printk("Call init!\n");
	
	gpio_addr = ioremap(GPIO_ADDR_BASE, GPIO_SIZE);
	if(gpio_addr == NULL)
	{
		printk("Mapping gpio_addr fail\n");
	}
	iomuxc_addr = ioremap(IOMUXC_ADDR_BASE,IOMUXC_SIZE);
	if(iomuxc_addr == NULL)
	{
		printk("Mapping gpio_addr fail\n");
		goto iomuxc_addr_fail;
	}
	iomuxc_gpio_mode(GPIO_21); 
	gpio_mode(GPIO_21,OUTPUT);
	gpio_write(GPIO_21,HIGH);
	return 0;
	
iomuxc_addr_fail:
	iounmap(gpio_addr);
	return -ENOMEM;
}

static void __exit led_exit(void)
{
	gpio_write(GPIO_21,LOW);
	iounmap(gpio_addr);
	iounmap(iomuxc_addr);
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
