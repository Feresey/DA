.PHONY :  all, clean
TARGET := ../lab04
SRC    := $(wildcard ../*.cpp)
HDR    := $(wildcard ../*.hpp ../*.h)
CXX    := g++
CFLAGS := -Wall -Wextra -Wpedantic -Wno-sign-compare -Wno-long-long -g3\
          -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Winit-self\
          -Wconversion -Wunreachable-code -Wsign-conversion

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o *.gc*

main.o: ../main.cpp $(HDR)
	$(CXX) $(CFLAGS) -c $<

%.o: ../%.cpp $(HDR)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET): $(SRC:../%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^
