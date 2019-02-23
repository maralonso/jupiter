EXEC    = jupitests

CFLAGS  = -c -g -fPIC -std=c99 -Wall -lgcov --coverage 
LDFLAGS = -lgcov --coverage

ALLSOURCES = $(wildcard *.c) $(wildcard cu/*.c) $(wildcard ../engine/**/*.c) $(wildcard ../engine/*.c)
EXCLUDES= ../engine/main.c
CSOURCES= $(filter-out $(EXCLUDES), $(ALLSOURCES))

VPATH=cu
VPATH=../engine

COBJECTS = $(CSOURCES:.c=.o)               

INCLUDES = -I ./cu -I ./  -I ./include -I ../engine -I ../engine/pieces/include

all: $(CSOURCES) $(EXEC) 

$(EXEC): $(COBJECTS)
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

