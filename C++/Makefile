CXX = g++
CXXFLAGS = -std=c++23 -Wall -Werror -Wextra -pedantic -Ofast

SRCS = $(wildcard *.cpp)
TARGETS = $(patsubst %.cpp,%,$(SRCS))

all: $(TARGETS)

alls: CXXFLAGS += -static
alls: all

.PHONY: all alls clean

$(TARGETS): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)


