CXX = g++

BUILD_DIR ?= ./build
OUTPUT_DIR ?= ./output
SRC_DIR ?= ./src

INC_DIRS := ./include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXXFLAGS ?= $(INC_FLAGS) -std=c++11 `pkg-config --cflags --libs opencv`

all: clean accumulate accumulateSquared accumulateWeighted addWeighted colorCorrectionMatrix channelExtract histogram lut gammaCorrection magnitude sum threshold reduce 

# c++ source
accumulate: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

accumulateSquared: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

accumulateWeighted: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

addWeighted: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

channelExtract: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

colorCorrectionMatrix: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

histogram: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

lut: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

gammaCorrection: lut
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$<_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

magnitude: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

reduce: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

sum: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

threshold: 
	$(CXX) $(SRC_DIR)/$@_cpu.cpp $(SRC_DIR)/$@_tb.cpp -o $(addprefix $(BUILD_DIR)/,$@) $(CXXFLAGS)

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)/* $(OUTPUT_DIR)/*

