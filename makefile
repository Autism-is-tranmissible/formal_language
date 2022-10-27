COMPILER = g++-12

FLAGS = -std=c++20 -Wall -Wextra -Wshadow -Wswitch-enum

# GMPS = -lgmpxx -lgmp

PATH_TO_HEADER = -I./header

FILES = 

TARGET = program

all: $(TARGET)

$(TARGET): $(TARGET).cpp $(shell find header -type f)
	$(COMPILER) $(FLAGS) $(PATH_TO_HEADER) $(FILES) $(TARGET).cpp -o $(TARGET)
# $(GMPS) must be at the end