# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# cpp files
SRC = constructive_heuristic.cpp city.cpp utils.cpp

# name of the executable
TARGET = tsp_constructive_heuristic

# build target
all: $(TARGET)

# rule to build the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Rule to run the program
run: $(TARGET)
	@echo "Running: ./$(TARGET) $(ARGS)"
	./$(TARGET) $(ARGS)

# clean executable
clean:
	rm -f $(TARGET)