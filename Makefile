-include Makefile.local
TOOLCHAIN ?= arm-none-eabi-
#CC := ${TOOLCHAIN}gcc
CXX := ${TOOLCHAIN}g++
LD := ${TOOLCHAIN}ld
OBJCOPY := ${TOOLCHAIN}objcopy

SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/$(_TARGET)/obj
BIN_DIR := $(BUILD_DIR)/$(_TARGET)/bin
DEP_DIR := $(BUILD_DIR)/dep
GEN_DIRS := $(OBJ_DIR) $(BIN_DIR) $(DEP_DIR)

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(subst $(SRC_DIR),$(OBJ_DIR),$(SRC_FILES:.cpp=.o))
DEP_FILES := $(subst $(SRC_DIR),$(DEP_DIR),$(SRC_FILES:.cpp=.d))

CFLAGS := -Wall -pedantic -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -ffunction-sections -fdata-sections 

# Set target specific flags
ifeq ($(_TARGET),release)
CFLAGS += -Os -g
endif
ifeq ($(_TARGET),debug)
CFLAGS += -g
endif

CXXFLAGS := $(CFLAGS) -std=c++11 -fno-rtti -fno-exceptions

# Better variable for flags passed directly to ld?
LDFLAGS := -Wl,-T $(SRC_DIR)/hw/tm4c1233h6pm.ld -Wl,--gc-sections

.DEFAULT_GOAL: all
.PRECIOUS: $(OBJ_DIR)/%.o $(BIN_DIR)/%.axf
.PHONY: build release debug clean

all: release debug
build: $(BIN_DIR)/truxter.bin
release:
	$(MAKE) _TARGET=release build
debug:
	$(MAKE) _TARGET=debug build

clean:
	rm -rf ${BUILD_DIR}

$(GEN_DIRS):
	@mkdir -p $@

$(BIN_DIR)/%.bin: $(BIN_DIR)/%.axf | $(BIN_DIR)
	@echo "BIN $^ -> $@"
	@$(OBJCOPY) -O binary $< $@

$(BIN_DIR)/%.axf: $(OBJ_FILES) | $(OBJ_DIR) $(BIN_DIR)
#Linking with g++ automatically provides libstdc++, libgcc and memcpy
	@echo "LD $^ -> $@"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "CC $^ -> $@"
	@mkdir -p `dirname $@`
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(DEP_DIR)/%.d: $(SRC_DIR)/%.cpp
	@echo "DEP $^ -> $@"
	@mkdir -p `dirname $@`
	@$(CXX) $(CXXFLAGS) -MM $< | sed "s@^.*:@$(OBJ_DIR)/$*.o $@:@" > $@

-include $(DEP_FILES)
