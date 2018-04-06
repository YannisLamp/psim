# Source, Includes
INCL   = exp_rand.h process.h dl_node.h process_queue.h priority_queue.h sem_queue.h
SRC    = main.cpp exp_rand.cpp process.cpp dl_node.cpp process_queue.cpp priority_queue.cpp sem_queue.cpp
OBJ    = $(SRC:.cpp=.o)
PROG   = psim

# Compiler, Linker Defines
CC      = g++ -std=gnu++0x
RM      = /bin/rm -f

# Compile and Assemble C++ Source Files into Object Files
%.o: %.cpp
	$(CC) -c $*.cpp

# Object Files into Binaries
$(PROG): $(OBJ)
	$(CC) -o $(PROG) $(OBJ)

# Objects depend on these Libraries
$(OBJ): $(INCL)

# Clean Up Objects, Exectuables
clean:
	$(RM) $(OBJ) $(PROG)
