.PHONY=all clean
KEYS=-Wall -Wextra  -pedantic -Wno-sign-compare -Wno-long-long -g3
TARGET=lab01
# CXX=zapcc++
CXX=g++
all: $(TARGET)

func.o: func.cpp struct.hpp 
	$(CXX) $(KEYS) func.cpp -c 

main.o: struct.hpp main.cpp
	$(CXX) $(KEYS) main.cpp -c

$(TARGET): main.o func.o 
	$(CXX) $(KEYS) -o $(TARGET) main.o func.o -lm

clean:
	rm -rf *.o lab01
