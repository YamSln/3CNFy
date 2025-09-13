# Params
CXX := g++ -MMD -MP
OPT = -O0
CXXFLAGS := -std=c++23 -Wall $(OPT)
LDFLAGS := -I/usr/include/gtest -lgtest -lgtest_main -lpthread

# Files
SRC_DIR := .
BUILD_DIR := ./build
TARGET_EXEC := $(BUILD_DIR)/encoder3
SRCS := $(shell find $(SRC_DIR) -name '*.cc' -not -path "$(SRC_DIR)/tests/*")
OBJS := $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(SRCS))
LIB_OBJS := $(filter-out $(BUILD_DIR)/main.o,$(OBJS))
DEPS := $(OBJS:.o=.d)

TEST_DIR = tests
TEST_BUILD = $(BUILD_DIR)/tests

all: $(TARGET_EXEC)

# Build process
$(TARGET_EXEC): $(OBJS)
	$(CXX) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

# Test process
TEST_SRCS := $(shell find $(TEST_DIR) -name '*.cc')
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cc,$(TEST_BUILD)/%.o,$(TEST_SRCS))
TEST_DEPS := $(TEST_OBJS:.o=.d)
TEST_EXEC := $(BUILD_DIR)/runTests

$(TEST_BUILD)/%.o: $(TEST_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run-tests: $(LIB_OBJS) $(TEST_OBJS)
	$(CXX) $(LIB_OBJS) $(TEST_OBJS) $(LDFLAGS) -o $(TEST_EXEC)
	./$(TEST_EXEC)

-include $(TEST_DEPS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET_EXEC)

.PHONY: all clean