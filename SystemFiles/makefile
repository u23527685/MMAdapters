# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Target executable
TARGET = main

# Source files
SRCS = main.cpp \
       Transaction.cpp \
       TransactionSnapshot.cpp \
       TransactionHistory.cpp \
       CreditCardPaymentStrategy.cpp \
       EWalletPaymentStrategy.cpp \
       EFTPaymentStrategy.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link all object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp into a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Run program
run: $(TARGET)
	./$(TARGET)
