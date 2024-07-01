# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I.

# SFML libraries to link against
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
COMPLEX_SRC = complex.cpp
MAIN_SRC = main.cpp
TEST_SRC = test.cpp

# Object files
COMPLEX_OBJ = complex.o
MAIN_OBJ = main.o
TEST_OBJ = test.o

# Output executables
TARGET = output
TEST_TARGET = test_output

# Default target to build both main executable and test executable
all: $(TARGET) $(TEST_TARGET)

# Rule to link object files to create the main executable
$(TARGET): $(COMPLEX_OBJ) $(MAIN_OBJ)
	$(CXX) $(COMPLEX_OBJ) $(MAIN_OBJ) -o $(TARGET) $(SFML_LIBS)

# Rule to link object files to create the test executable
$(TEST_TARGET): $(COMPLEX_OBJ) $(TEST_OBJ)
	$(CXX) $(COMPLEX_OBJ) $(TEST_OBJ) -o $(TEST_TARGET) $(SFML_LIBS)

# Rule to compile complex.cpp to complex.o
$(COMPLEX_OBJ): $(COMPLEX_SRC)
	$(CXX) $(CXXFLAGS) -c $(COMPLEX_SRC) -o $(COMPLEX_OBJ)

# Rule to compile main.cpp to main.o
$(MAIN_OBJ): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

# Rule to compile test.cpp to test.o
$(TEST_OBJ): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

# Rule to clean up build files
clean:
	rm -f $(COMPLEX_OBJ) $(MAIN_OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)

# Declare 'all' and 'clean' as phony targets
.PHONY: all clean
