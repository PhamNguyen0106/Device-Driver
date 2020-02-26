//module.h dinh nghia cac macro nhu module_init 
//va module_exit
#include <linux/module.h>
#include <linux/fs.h>/*Dinh nghia cac ham cap phat/giai phong device number*/
#include <linux/device.h>/*chua function phuc vu viec tao device file*/
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>/*thu vien cho ham copy from -to...*/
#include <linux/interrupt.h>
#include <linux/ioctl.h>
#include <asm/io.h>
#include <linux/err.h>
//Lib for timer
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <asm/param.h>


#define DRIVER_AUTHOR "Pham Dang Nguyen <dangnguyen0106@gmail.com>"
#define DRIVER_DESC   "A sample loadable kernel module"
#define DRIVER_VERSION "0.1"

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
//#define LED				0

#define GPIO_SET_BIT(x)				(1 << x)
#define GPIO_CLEAR_BIT(x)			~(1 << x)
#define GPIO_CLEAR_DR				0

unsigned int __iomem *gpio_addr;
unsigned int __iomem *iomuxc_addr;
/*Luu device Number*/
struct _vchar_drv{
    dev_t dev_num;//register device number
    struct class *dev_class;//tao class trong /sys/class de quan ly cac device 
    struct device *dev;//tao ra dc dvFile trong /dev/
}vchar_drv;
static struct cdev c_dev; // Global variable for the character device structure
struct timer_list exp_timer;//counter timer
static char command[256];
static char response[256];
int have_command = 0;
int LED = 0;


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

static void do_something(unsigned long data)
{
	printk(KERN_INFO "Your timer expired and app has been called\n");
	LED = LED ^ 1;
	gpio_write(GPIO_21,LED);
    mod_timer(&exp_timer, jiffies + 1*HZ);
}

static int __init init_start_kernel(void)
{
    int ret = 0;
	int delay = 1;
    printk("start device number\n");
    /*cap phat Tinh device number*/
    /*vchar_drv.dev_num = MKDEV(255,0);
    ret = register_chrdev_region(vchar_drv.dev_num,1,"char_Device_Driver");*/
    /*cap phat dong device number*/
    vchar_drv.dev_num = 0;
    ret = alloc_chrdev_region(&vchar_drv.dev_num,0,1,"vchar_device");
    printk("allocated char device number (%d,%d)\n",MAJOR(vchar_drv.dev_num),MINOR(vchar_drv.dev_num));
    if(ret < 0)
    {
        printk("Fail to register Device Number\n");
        goto fail_register_devnum;
    }
    /*Create device file*/
    vchar_drv.dev_class = class_create(THIS_MODULE, "class_vchar_dev");
    if(vchar_drv.dev_class == NULL)
    {
        printk("fail to create device class\n");
        goto failed_create_class;
    }
    vchar_drv.dev = device_create(vchar_drv.dev_class,NULL,vchar_drv.dev_num,NULL,"vchar_dev");
    if(IS_ERR(vchar_drv.dev))
    {
        printk("fail to create device\n");
        goto failed_create_device;
    }
    // cdev_init(&c_dev, &my_fops);
    // if (cdev_add(&c_dev, vchar_drv.dev_num, 1) == -1)
    // {
    //     device_destroy(vchar_drv.dev_class, vchar_drv.dev_num);
    //     class_destroy(vchar_drv.dev_class);
    //     unregister_chrdev_region(vchar_drv.dev_num, 1);
    //     return -1;
    // }
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
	//gpio_write(GPIO_21,HIGH);
    printk("Initialize char device driver successsfully\n");
	printk(KERN_INFO "Init timer called\n");
	init_timer_on_stack(&exp_timer);
	exp_timer.expires = jiffies + delay * HZ;
	exp_timer.data = 0;
	exp_timer.function = do_something;
	add_timer(&exp_timer);

    return 0;
    failed_create_class:
        unregister_chrdev_region(vchar_drv.dev_num,1);
    failed_create_device:
        class_destroy(vchar_drv.dev_class);
    fail_register_devnum: 
        return ret;
    iomuxc_addr_fail:
	iounmap(gpio_addr);
	    return -ENOMEM;
}

static void __exit remove_kernel(void)
{
    /*delete device file*/
    cdev_del(&c_dev);
    device_destroy(vchar_drv.dev_class,vchar_drv.dev_num);
    class_destroy(vchar_drv.dev_class);
    unregister_chrdev_region(vchar_drv.dev_num,1);
    gpio_write(GPIO_21,LOW);
	iounmap(gpio_addr);
	iounmap(iomuxc_addr);
	del_timer(&exp_timer);  
    printk("exit char device driver\n");
}

module_init(init_start_kernel);
module_exit(remove_kernel);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("testdevice");/*kieu device ma module ho tro*/
