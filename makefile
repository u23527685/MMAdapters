# === Makefile for Observer and Command Pattern Tests ===

CXX = g++
CXXFLAGS = -std=c++17 -Wall

# === Targets ===
OBSERVER_TARGET = TestObserver
COMMAND_TARGET = TestCommand

# === Object files ===
OBSERVER_OBJS = PlantInventory.o TestObserver.o
COMMAND_OBJS = PlantStock.o addStock.o removeStock.o TestStockCommands.o

# === Default target builds both ===
all: $(OBSERVER_TARGET) $(COMMAND_TARGET)

# === Observer Pattern Build ===
PlantInventory.o: PlantInventory.cpp PlantInventory.h InventoryObserver.h
	$(CXX) $(CXXFLAGS) -c PlantInventory.cpp

TestObserver.o: TestObserver.cpp PlantInventory.h InventoryObserver.h
	$(CXX) $(CXXFLAGS) -c TestObserver.cpp

$(OBSERVER_TARGET): $(OBSERVER_OBJS)
	$(CXX) $(CXXFLAGS) $(OBSERVER_OBJS) -o $(OBSERVER_TARGET)

# === Command Pattern Build ===
PlantStock.o: PlantStock.cpp PlantStock.h
	$(CXX) $(CXXFLAGS) -c PlantStock.cpp

addStock.o: addStock.cpp addStock.h PlantStock.h
	$(CXX) $(CXXFLAGS) -c addStock.cpp

removeStock.o: removeStock.cpp removeStock.h PlantStock.h
	$(CXX) $(CXXFLAGS) -c removeStock.cpp

TestStockCommands.o: TestStockCommands.cpp PlantStock.h addStock.h removeStock.h
	$(CXX) $(CXXFLAGS) -c TestStockCommands.cpp

$(COMMAND_TARGET): $(COMMAND_OBJS)
	$(CXX) $(CXXFLAGS) $(COMMAND_OBJS) -o $(COMMAND_TARGET)

# === Run both tests ===
run: $(OBSERVER_TARGET) $(COMMAND_TARGET)
	@echo "=== Running Observer Pattern Test ==="
	./$(OBSERVER_TARGET)
	@echo "\n=== Running Command Pattern Test ==="
	./$(COMMAND_TARGET)

# === Clean up ===
clean:
	rm -f *.o $(OBSERVER_TARGET) $(COMMAND_TARGET)

