.PHONY=all clean
KEYS=-std=c++14 -Wall -Wextra -Werror -pedantic -Wno-sign-compare -Wno-long-long 
TARGET=lab01
CXX=g++

all: $(TARGET)

struct.o: struct.cpp struct.hpp 
	$(CXX) $(KEYS) struct.cpp -c 

main.o: struct.hpp main.cpp
	$(CXX) $(KEYS) main.cpp -c

$(TARGET): main.o struct.o 
	$(CXX) $(KEYS) -o $(TARGET) main.o struct.o -lm

clean:
	rm -rf *.o lab01
