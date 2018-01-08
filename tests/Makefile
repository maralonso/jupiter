EXEC    = engine-tests

CFLAGS  = -c -g -Wall
LDFLAGS = -Lcu/ -lcu

CSOURCES = $(wildcard *.c) 
CSOURCES += ../engine/generation.c

COBJECTS = $(CSOURCES:.c=.o)               

INCLUDES = -I cu/ \
		  -I ../engine/ 


all: $(CSOURCES) $(EXEC) 

$(EXEC): $(COBJECTS)
	$(CC) $(INCLUDES) $(COBJECTS) -o $@ $(LDFLAGS)
	rm -rf *.o                               
	@echo ''
	@echo 'Finished building target $@'


%.o: %.c
		$(CC) $(INCLUDES) $(CFLAGS) $< -o $@


clean:
		rm -rf *.o
		rm -rf $(EXEC)

