# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

# Output binary name
TARGET = plant_app

# Source files
SRCS = main.cpp \
       BasePlant.cpp \
       PlantDecorator.cpp \
       GiftWrap.cpp \
       DecorativePot.cpp \
       SpecialArrangement.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Header dependencies
DEPS = Plant.h BasePlant.h PlantDecorator.h GiftWrap.h DecorativePot.h SpecialArrangement.h

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp to .o
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) *.o

# Run target
run: $(TARGET)
	./$(TARGET)
