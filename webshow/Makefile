NAME := webshow

EXE := $(NAME).exe

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.c=.o)

CFLAGS :=  -Wall -Wextra -Werror -Wundef

LDFLAGS := -Wl,--subsystem,windows -shared-libgcc \
		-Wl,--enable-auto-import -loleaut32 -lole32

CC := gcc

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o *.exe

.PHONY: clean
