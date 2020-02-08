.PHONY :  all, clean
TARGET := $(shell basename $(shell pwd))
SRC    := $(wildcard *.cpp)
HDR    := $(wildcard *.hpp)
CXX    := g++
CFLAGS := -fsanitize=address -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3 #-lm #-pg -DDMALLOC -DDMALLOC_FUNC_CHECK -I/usr/local/include -L/usr/local/lib


all: $(TARGET)

clean:
	rm -f $(TARGET) $(SRC:%.cpp=%.o)

$(TARGET): $(SRC:%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^

main.o: main.cpp $(HDR) 
	$(CXX) $(CFLAGS) -c main.cpp

%.o: %.cpp %.hpp
	$(CXX) $(CFLAGS) -c -o $@ $< -lm
