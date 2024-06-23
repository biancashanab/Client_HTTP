CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra 
LDFLAGS = -lssl -lcrypto

SRC_DIR = Source
OBJ_DIR = build
BIN_DIR = bin
INCLUDE_DIR = Header

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/http_client

PYTHON = python3
PYTHON_SCRIPT = API.py

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(INCLUDE_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR) $(INCLUDE_DIR):
	mkdir -p $@

run:
	$(PYTHON) $(PYTHON_SCRIPT)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run clean