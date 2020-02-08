.PHONY  :  all, clean
TARGET  = $(shell basename $(shell pwd))
SRC     = $(wildcard *.cpp)
HDR     = $(wildcard *.hpp)
CXX     = g++
CFLAGS  = -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3\
          -Weffc++ -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Winit-self \
          -Wconversion -Wsign-conversion -Wunreachable-code -fstack-protector 
# LDFLAGS = -lgcov  #-ltcmalloc

all: $(TARGET)

clean:
	rm -f $(TARGET) $(SRC:%.cpp=%.o) *.gcno *.gcda

$(TARGET): $(SRC:%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^ -lm

main.o: main.cpp $(HDR) 
	$(CXX) $(CFLAGS) -c main.cpp

%.o: %.cpp %.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
