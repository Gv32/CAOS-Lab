USER_APP = user_app
obj-m += es5.o 
es5-objs := device.o shared.o

PWD := $(CURDIR) 
 
all: 
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
	$(CC) -o $(USER_APP) $(USER_APP).c shared.c
 
clean: 
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm $(USER_APP)
