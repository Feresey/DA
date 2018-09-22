.PHONY=all clean
KEYS=-pedantic -Wall -Wextra -Wpedantic -Werror -Wno-sign-compare -Wno-long-long -lm -g3
TARGET=lab01
CXX=g++

all: $(TARGET)

struct.o: struct.cpp struct.hpp 
	$(CXX) $(KEYS) struct.cpp -c 

main.o: struct.hpp main.cpp
	$(CXX) $(KEYS) main.cpp -c

$(TARGET): main.o struct.o 
	$(CXX) $(KEYS) -o $(TARGET) main.o struct.o 

clean:
	rm -rf *.o $(TARGET)
