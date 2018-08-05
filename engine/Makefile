EXEC    = jupiter

CFLAGS  = -c -fPIC -std=c99 -Wall -Werror
DBCFLAGS  = -c -g -fPIC -std=c99 -Wall -Werror -lgcov --coverage
LDFLAGS =
DBLDFLAGS = -lgcov --coverage

CSOURCES = $(wildcard *.c) $(wildcard pieces/*.c)

VPATH = pieces

COBJECTS = $(CSOURCES:.c=.o)               

INCLUDES = -I ./ -I pieces/include

LIBS = 

all: $(CSOURCES) $(EXEC) 

debug:
	@$(MAKE) CFLAGS="$(DBCFLAGS)" LDFLAGS="$(DBLDFLAGS)"


$(EXEC): $(COBJECTS)
	$(CC) $(COBJECTS) $(LDFLAGS) -o $@
	rm -rf *.o
	@echo ''
	@echo 'Finished building target $@'

%.o: %.c
		$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
		rm -rf *.o
		rm -rf pieces/*.o
		rm -rf $(EXEC)

