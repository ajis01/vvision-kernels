CXX = g++

BUILD_DIR ?= ./build
SRC_DIR ?= ./src

INC_DIRS := ./include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXXFLAGS ?= $(INC_FLAGS) -std=c++11 `pkg-config --cflags --libs opencv`

all: clean accumulate

# c++ source
accumulate: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)/*

