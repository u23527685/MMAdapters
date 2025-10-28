CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = main

SRCS = CommandObserverMain.cpp AddStock.cpp RemoveStock.cpp PlantStock.cpp PlantInventory.cpp InventoryObserver.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
