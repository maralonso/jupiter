LIBRARY = chess-engine.a
EXEC    = engine

CFLAGS  = -c -g -fPIC -Wall
LDFLAGS =

CSOURCES = generation.c

COBJECTS = $(CSOURCES:.c=.o)               

INCLUDES = 

LIBS = 


all: $(CSOURCES) $(LIBRARY) 

lib: $(LIBRARY) 

debug: $(CSOURCES) $(EXEC)

$(LIBRARY): $(COBJECTS)
	@echo 'Building Library: $@'
	ar rcs $@ $(LDFLAGS) $(LIBS) $(COBJECTS) 
	rm -rf *.o                               
	@echo ''
	@echo 'Finished building target $@'


                                 
$(EXEC): $(COBJECTS)
	$(CC) $(CFLAGS) debug_main.c -o debug_main.o
	$(CC) debug_main.o $(COBJECTS) -o $@                     
	rm -rf *.o                               
	@echo ''
	@echo 'Finished building target $@'

%.o: %.c
		$(CC) $(INCLUDES) $(CFLAGS) $< -o $@


clean:
		rm -rf *.o
		rm -rf $(LIBRARY)
		rm -rf $(EXEC)

