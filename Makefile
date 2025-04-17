CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Isrc

SRC_DIR := src
TEST_DIR := tests

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

OUT := mbimros
TEST_SRCS := $(TEST_DIR)/test_mbim.cpp
TEST_OUTPUT := test_mbim

all: $(OUT)

$(OUT): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test:
	$(CXX) $(CXXFLAGS) $(filter-out src/main.cpp, $(SRCS)) $(TEST_SRCS) -o $(TEST_OUTPUT)
	./$(TEST_OUTPUT)

clean:
	rm -f $(OUT) $(TEST_OUTPUT)

.PHONY: all clean test
