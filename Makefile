# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Source files
SRC = constructive_heuristic.cpp city.cpp

# Output executable
TARGET = tsp_constructive_heuristic

# Build target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean up build artifacts
clean:
	rm -f $(TARGET)