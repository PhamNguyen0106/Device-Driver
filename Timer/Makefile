ARCH = arm

CROSS_COMPILE=arm-linux-gnueabihf-

OUTPUT=Led_Timer


TARGET_IP = 192.168.1.119

obj-m := $(OUTPUT).o 

KDIR  := ~/Documents/udoo-dev/linux_kernel/

PWD   := $(shell pwd)

all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) -C $(KDIR) modules
	
clean:
	@rm -Rf *.o *.ko *.mod.c modules.order Module.symvers
	
install:
	sshpass -p "udooer" scp $(OUTPUT).ko udooer@$(TARGET_IP):~
