CC       := g++
CXXFLAGS := -std=c++23 -I.

TEST_SRC := .\test\main.cpp
TEST_BIN := .\test\test

.PHONY: all run

all:
	$(CC) $(CXXFLAGS) -o $(TEST_BIN) $(TEST_SRC)

run: all
	$(TEST_BIN)
