CXX = g++
CXXFLAGS = -std=c++23 -Wall -Werror -Wextra -pedantic -Ofast

SRCS = $(wildcard *.cpp)
TARGET = main

all: $(TARGET)

alls: CXXFLAGS += -static
alls: all

.PHONY: all alls clean

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)


