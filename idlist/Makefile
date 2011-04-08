NAME := idlist

EXE := $(NAME).exe

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

CXXFLAGS :=  -Wall -Wextra -Werror -Wundef

LDFLAGS := -mwindows

CXX := g++

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o *.exe

.PHONY: clean
