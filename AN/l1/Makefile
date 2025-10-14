CXX = g++
CXXFLAGS = -Wall -Werror -Wextra

SRCS = $(wildcard *.cpp)
TARGETS = $(patsubst %.cpp,%,$(SRCS))

all: $(TARGETS)

.PHONY: all clean

$(TARGETS): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)


