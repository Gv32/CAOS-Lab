PWD := $(CURDIR)

obj-m += ex2.o
ex2-objs = main.o uart.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
