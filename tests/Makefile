EXEC    = engine-tests

CFLAGS  = -c -g -fPIC -Wall
LDFLAGS =

CSOURCES = $(wildcard *.c) 
CSOURCES += cutest-1.5/CuTest.c 
CSOURCES += ../engine/generation.c

COBJECTS = $(CSOURCES:.c=.o)               

INCLUDES = -I cutest-1.5/ \
		  -I ../engine/ 


all: $(CSOURCES) $(EXEC) 

$(EXEC): $(COBJECTS)
	$(CC) $(LDFLAGS) $(INCLUDES) $(COBJECTS) -o $@
	rm -rf *.o                               
	@echo ''
	@echo 'Finished building target $@'


%.o: %.c
		$(CC) $(INCLUDES) $(CFLAGS) $< -o $@


clean:
		rm -rf *.o
		rm -rf $(LIBRARY)
		rm -rf $(EXEC)

