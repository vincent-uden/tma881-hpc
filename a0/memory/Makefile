TARGET_EXEC ?= a.out
TEST_EXEC ?= test.out

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

TEST_BUILD_DIR ?= ./test_build

SRCS := $(shell find $(SRC_DIRS) -name "[!.]*.cpp" -or -name *.c -or -name *.s )
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

TEST_SRC_DIRS ?= ./src ./test
TEST_SRCS = ./src/matrix.c ./test/test.c
TEST_OBJS := $(TEST_SRCS:%=$(TEST_BUILD_DIR)/%.o)
TEST_DEPS := $(TEST_OBJS:.o=.d)

TEST_INC_DIRS := $(shell find $(TEST_SRC_DIRS) -type d)
TEST_INC_FLAGS := $(addprefix -I,$(TEST_INC_DIRS))

CFLAGS ?= $(INC_FLAGS) -MMD -MP -g
LDFLAGS =
CC = gcc
CXX = g++

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@



$(TEST_BUILD_DIR)/$(TEST_EXEC): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $@ $(LDFLAGS)

# assembly
$(TEST_BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(TEST_BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(TEST_BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(TEST_BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

run:
	./build/a.out

crun: $(BUILD_DIR)/$(TARGET_EXEC)
	./build/a.out

test: $(TEST_BUILD_DIR)/$(TEST_EXEC)
	$(RM) matrix.txt
	$(MKDIR_P) test_build
	./test_build/test.out


profile: CFLAGS += -pg
profile: LDFLAGS += -pg
profile: $(BUILD_DIR)/$(TARGET_EXEC)

stacktrace: CFLAGS += -v -da -Q
stacktrace: $(BUILD_DIR)/$(TARGET_EXEC)
