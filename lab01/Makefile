.PHONY=all clean
KEYS=-Wall -Wextra  -pedantic -Wno-sign-compare -Wno-long-long -g3
TARGET=lab01

all: $(TARGET)

func.o: func.cpp struct.hpp 
	g++ $(KEYS) func.cpp -c 

main.o: struct.hpp main.cpp
	g++ $(KEYS) main.cpp -c

$(TARGET): main.o func.o 
	g++ $(KEYS) -o $(TARGET) main.o func.o -lm

clean:
	rm -rf *.o lab01