CC = g++

# Default MAX_DATA value; override by running, e.g., `make MAX_DATA=2000000`
MAX_DATA ?= 1000000

CFLAGS = -Ofast -march=native -fopenmp -fopenmp-simd -DMAX_DATA=$(MAX_DATA)

# Target executable name and source files
TARGET = prog_cpp
SRCS = main.cpp

# Rule to build the target executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean up generated files
.PHONY: clean
clean:
	rm -f $(TARGET)
