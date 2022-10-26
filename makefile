COMPILER = g++

FLAGS = -std=c++17 -Wall -Wextra -Wshadow -Wswitch-enum

# GMPS = -lgmpxx -lgmp

PATH_TO_HEADER = -I./header

FILES = 

HEADERS = header/numbers.h header/variables.h header/functions.h

TARGET = program

all: $(TARGET)

$(TARGET): $(TARGET).cpp $(HEADERS)
	$(COMPILER) $(FLAGS) $(PATH_TO_HEADER) $(FILES) $(TARGET).cpp -o $(TARGET)
# $(GMPS) must be at the end