CC       := g++
CXXFLAGS := -std=c++23 -I.

TEST_SRC := .\test\main.cpp
TEST_BIN := .\test\test

TEST_FLAG := ZLOG_T

.PHONY: all final run

all:
	$(CC) $(CXXFLAGS) -o $(TEST_BIN) $(TEST_SRC) -D$(TEST_FLAG)

final:
	$(CC) $(CXXFLAGS) -o $(TEST_BIN) $(TEST_SRC)

run: all
	$(TEST_BIN)
