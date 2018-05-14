EXEC    = jupiter

CFLAGS  = -c -g -fPIC -std=c99 -Wall -Werror
LDFLAGS =

CSOURCES = $(wildcard *.c) $(wildcard pieces/*.c)

VPATH = pieces

COBJECTS = $(CSOURCES:.c=.o)               

INCLUDES = -I ./ -I pieces/include

LIBS = 


all: $(CSOURCES) $(EXEC) 

lib: $(LIBRARY) 

debug: $(CSOURCES) $(EXEC)
                                
$(EXEC): $(COBJECTS)
	$(CC) $(COBJECTS) -o $@                     
	rm -rf *.o                               
	@echo ''
	@echo 'Finished building target $@'

%.o: %.c
		$(CC) $(INCLUDES) $(CFLAGS) $< -o $@


clean:
		rm -rf *.o
		rm -rf pieces/*.o
		rm -rf $(EXEC)

