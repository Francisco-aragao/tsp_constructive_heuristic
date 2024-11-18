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

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

all_tests:
	./run_tsp.sh

# Clean up build artifacts
clean:
	rm -f $(TARGET)