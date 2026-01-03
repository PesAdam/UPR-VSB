CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -fsanitize=address
LDFLAGS = -fsanitize=address

SRCS = main.c player.c loader.c output.c
OBJS = $(SRCS:.c=.o)
TARGET = lol-stats

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) output.html
