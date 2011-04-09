NAME := winspec

EXE := $(NAME).exe

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

CFLAGS :=  -Wall -Wextra -Werror -Wundef

LDFLAGS :=

CC := gcc

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o *.exe

.PHONY: clean
