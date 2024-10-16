# Variables
# Compiler
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as
# Compiler flags
CFLAGS = -g -mcpu=cortex-m4

# Target executable 
TARGET = main.elf
# Source files
SRCS = main.c delay.c startup.s
# Object files
OBJS = startup.o main.o delay.o

# Rules 
# Default target
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJS)
	$(LD) -T linker.ld $(OBJS) -o $(TARGET)

# Rule to compile source files into object files
main.o: main.c
	$(CC) $(CFLAGS) -c -mthumb main.c -o main.o
delay.o: delay.c
	$(CC) $(CFLAGS) -c -mthumb delay.c -o delay.o
startup.o: startup.s
	$(AS) $(CFLAGS) startup.s -o startup.o

# Clean rule to remove compiled files
clean:
	rm -f *.o 
	rm -f *.elf
