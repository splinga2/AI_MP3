CC = g++

SRC := $(shell find . -name '*.cpp' -or -name '*.h')

CC_FLAGS = -Wall -Wextra -Werror -std=c++11 -pedantic

EXE = part2

all: $(SRC)
	$(CC) $(SRC) $(CC_FLAGS) -o $(EXE)

clean:
	rm -rf $(EXE)
