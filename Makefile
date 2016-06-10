CFLAGS=-g -O2
  
SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< -lz
clean: 
	rm -f $(PROGS) *.o
