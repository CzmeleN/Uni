CXX = g++
CXXFLAGS = -std=c++23 -Wall -Werror -Wextra -pedantic -Ofast

SRCS = $(wildcard *.cpp)
TARGET = main

all: $(TARGET)

no-elide: CXXFLAGS += -fno-elide-constructors
no-elide: all

alls: CXXFLAGS += -static
alls: all

.PHONY: all alls clean

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

assm:
	$(CXX) $(CXXFLAGS) -S -fverbose-asm -g tabbit.cpp
