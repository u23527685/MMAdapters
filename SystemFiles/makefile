# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

# ------------------------
# Combined Project Target
# ------------------------
TARGET = main

# Source files
SRCS = main.cpp \
       Transaction.cpp \
       TransactionSnapshot.cpp \
       TransactionHistory.cpp \
       CreditCardPaymentStrategy.cpp \
       EWalletPaymentStrategy.cpp \
       EFTPaymentStrategy.cpp \
       BasePlant.cpp \
       PlantDecorator.cpp \
       GiftWrap.cpp \
       DecorativePot.cpp \
       SpecialArrangement.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header dependencies (optional, for automatic recompilation)
DEPS = Transaction.h TransactionSnapshot.h TransactionHistory.h \
       CreditCardPaymentStrategy.h EWalletPaymentStrategy.h EFTPaymentStrategy.h \
       Plant.h BasePlant.h PlantDecorator.h GiftWrap.h DecorativePot.h SpecialArrangement.h

# Default target
all: $(TARGET)

# Link objects into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp to .o
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) *.o

# Run program
run: $(TARGET)
	./$(TARGET)
