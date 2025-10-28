# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Target executable
TARGET = transaction_app

# Source and object files
SRCS = main.cpp \
       Transaction.cpp \
       CreditCardPaymentStrategy.cpp \
       EWalletPaymentStrategy.cpp \
       EFTPaymentStrategy.cpp

OBJS = $(SRCS:.cpp=.o)

# Header dependencies
DEPS = Transaction.h \
       PaymentStrategy.h \
       CreditCardPaymentStrategy.h \
       EWalletPaymentStrategy.h \
       EFTPaymentStrategy.h

# Default rule
all: $(TARGET)

# Link all object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each source file to object file
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program (build first if necessary)
run: $(TARGET)
	./$(TARGET)

# Clean rule
clean:
	rm -f *.o $(TARGET)
