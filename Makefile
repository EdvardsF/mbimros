CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Isrc

SRC_DIR := src
TEST_DIR := tests

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
TEST_SRCS := $(shell find $(TEST_DIR) -name '*.cpp')

OUT := mbimros
TEST_OUT := test_mbimros

all: $(OUT)

$(OUT): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build and run all tests
test: $(TEST_OUT)
	./$(TEST_OUT)

# Only build tests, don't run
$(TEST_OUT): $(filter-out $(SRC_DIR)/main.cpp, $(SRCS)) $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run a specific test file
test_one:
	$(CXX) $(CXXFLAGS) $(filter-out $(SRC_DIR)/main.cpp, $(SRCS)) tests/catch_config.cpp $(TEST_FILE) -o single_test
	./single_test

clean:
	rm -f $(OUT) $(TEST_OUT) single_test

.PHONY: all clean test test_one
