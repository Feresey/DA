.PHONY :  all, clean
TARGET := ../lab09
SRC    := $(wildcard ../*.cpp)
HDR    := $(wildcard ../*.hpp ../*.h)
CXX    := zapcc++ -std=c++1z
CFLAGS := -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3\
          -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Winit-self\
          -Wconversion -Wsign-conversion -Wunreachable-code -Wno-comment#-fsanitize=address #-fprofile-arcs -ftest-coverage  

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o *.gc*

main.o: ../main.cpp $(HDR)
	$(CXX) $(CFLAGS) -c $<

%.o: ../%.cpp $(HDR)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET): $(SRC:../%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^ -lm
