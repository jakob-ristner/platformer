TARGET_EXEC ?= a.out
WIN_TARGET ?= a.exe

BUILD_DIR ?= ./build
WIN_BUILD ?= ./win_build
SRC_DIRS ?= ./lib ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -g -I./include -I./lib
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++
CXX = g++
WIN_CC = i686-w64-mingw32-g++

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r ./build/classes
	$(RM) -r $(BUILD_DIR)/$(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p

run:
	./build/a.out

crun: $(BUILD_DIR)/$(TARGET_EXEC)
	./build/a.out

profile: CPPFLAGS += -pg
profile: LDFLAGS += -pg
profile: $(BUILD_DIR)/$(TARGET_EXEC)

stacktrace: CPPFLAGS += -v -da -Q
stacktrace: $(BUILD_DIR)/$(TARGET_EXEC)

win: CC = $(WIN_CC)
win: CXX = $(WIN_CC)
win: BUILD_DIR = $(WIN_BUILD)
win: TARGET_EXEC = $(WIN_TARGET)
win: $(BUILD_DIR)/$(TARGET_EXEC)
