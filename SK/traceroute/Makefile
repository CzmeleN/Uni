# Jan Mączyński 344907

CC = gcc
CFLAGS = -std=gnu17 -Wall -Werror -Wextra -pedantic -Ofast

SRCS = traceroute.c
OBJS = $(SRCS:.c=.o)
TARGET = traceroute

all: $(TARGET)

.PHONY: all clean distclean

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(TARGET)
