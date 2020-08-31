CC = gcc
TARGETS = malloc_cyclic manipulation
CFLAGS = -Wall -Wextra -g -O2


all : build

build : $(TARGETS)

strip :
	strip $(TARGETS) 

bin/% : %.c
	$(CC) $(CFLAGS) $< -o $@


.PHONY	: clean

clean : 
	-rm -rf $(TARGETS)


