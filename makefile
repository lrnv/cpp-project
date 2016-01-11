CC = g++
CFLAGS = -fpermissive -g

SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)
AOUT = main

all : $(AOUT)

$(AOUT) : $(OBJS)
	$(CC) -o $@ $^
	
%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<
	
clean :
	@rm *.o $(AOUT)

test : all
	./$(AOUT)
