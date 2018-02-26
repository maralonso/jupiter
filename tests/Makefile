EXEC    = jupitests

CFLAGS  = -c -g -Wall -std=c99
LDFLAGS = -L../engine -lchessengine

CSOURCES = $(wildcard *.c) $(wildcard cu/*.c)

VPATH=cu

COBJECTS = $(CSOURCES:.c=.o)               

INCLUDES = -I ./cu -I ./  -I ./include -I ../engine

all: $(CSOURCES) $(EXEC) 

$(EXEC): $(COBJECTS)
	make -C ../engine
	@echo ''
	$(CC) $(INCLUDES) $(COBJECTS) -o $@ $(LDFLAGS)
	rm -rf *.o                               
	@echo ''
	@echo 'Finished building target $@'

%.o: %.c
		$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
		make -C ../engine clean
		rm -rf *.o
		rm -rf $(EXEC)

