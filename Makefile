-include Makefile.local
TOOLCHAIN ?= arm-none-eabi-
#CC := ${TOOLCHAIN}gcc
CXX := ${TOOLCHAIN}g++
LD := ${TOOLCHAIN}ld
OBJCOPY := ${TOOLCHAIN}objcopy


SRC_DIR := src

OBJ_DIR := obj
BIN_DIR := bin
DEP_DIR := dep
GEN_DIRS := $(OBJ_DIR) $(BIN_DIR) $(DEP_DIR)

SRC_FILES := $(wildcard src/*.cpp) $(wildcard src/hw/*.cpp)
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.cpp=.o)))
DEP_FILES := $(addprefix $(DEP_DIR)/,$(notdir $(SRC_FILES:.cpp=.d)))

CFLAGS := -g -std=c++11 -Wall -pedantic -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions
#-e _ZN9interrupt12vector_resetEv
#--verbose
#-Os
CXXFLAGS := $(CFLAGS)

# Better variable for flags passed directly to ld?
LDFLAGS := -Wl,-T $(SRC_DIR)/hw/tm4c123gh6pm.ld -Wl,--gc-sections
#-Wl,--verbose
#-e start


.DEFAULT_GOAL: all
.PRECIOUS: $(OBJ_DIR)/%.o $(BIN_DIR)/%.axf


all: $(BIN_DIR)/truxter.bin

clean:
	rm -rf $(GEN_DIRS)

$(GEN_DIRS):
	mkdir -p $@

$(BIN_DIR)/%.bin: $(BIN_DIR)/%.axf | $(BIN_DIR)
	$(OBJCOPY) -O binary $< $@

$(BIN_DIR)/%.axf: $(OBJ_FILES) | $(OBJ_DIR) $(BIN_DIR)
#Linking with g++ automatically provides libstdc++, libgcc and memcpy
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o:src/%.cpp | $(OBJ_DIR) $(DEP_DIR)
	$(CXX) $(CXXFLAGS) -MD -MF $(DEP_DIR)/$*.d -c -o $@ $<

-include $(DEP_FILES)
