CC = g++
CFLAGS = -fpermissive -g

SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)
AOUT = a.out

all : $(AOUT)

a.out : $(OBJS)
	$(CC) -o $@ $^
	
%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<
	
clean :
	@rm *.o
