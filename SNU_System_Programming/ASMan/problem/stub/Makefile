# Avoid built-in rules in Makefile
.SUFFIXES:

# Do not remove intermediate files
.PRECIOUS: %.s %.o

# Avoid any unnecessary instructions
CFLAGS += -fverbose-asm
CFLAGS += -fno-asynchronous-unwind-tables
CFLAGS += -fcf-protection=none

OPT = -O0

CC = gcc

SRCS += $(wildcard *.c)
EXES += $(patsubst %.c, %, $(SRCS))

all: $(EXES)

%.s: %.c
	gcc $(CFLAGS) $(OPT) -S $< -o $@

%.o: %.s
	gcc $(CFLAGS) -c $< -o $@

%: %.o
	gcc $< -o $@

clean:
	rm -f *.o *.s $(EXES)

