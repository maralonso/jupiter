EXEC    = engine-tests

CFLAGS  = -c -g -Wall -std=c99
LDFLAGS = -Lcu/ -lcu -L../engine -lchessengine

CSOURCES = $(wildcard *.c) 

COBJECTS = $(CSOURCES:.c=.o)               

INCLUDES = -I cu/ \
		  -I ../engine


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
		rm -rf *.o
		rm -rf $(EXEC)

