CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

TARGET = main

SOURCES = main.cpp \
          PlantStock.cpp \
          PlantInventory.cpp \
          AddStock.cpp \
          RemoveStock.cpp \
          StaffObserver.cpp \
          SalesFloorObserver.cpp \
		  InventoryObserver.cpp

OBJECTS = $(SOURCES:.cpp=.o)

HEADERS = PlantStock.h \
          PlantInventory.h \
          InventoryObserver.h \
          StockCommand.h \
          AddStock.h \
          RemoveStock.h \
          StaffObserver.h \
          SalesFloorObserver.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all