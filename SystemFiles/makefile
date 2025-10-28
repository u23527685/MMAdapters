# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

# ------------------------
# Plant Decorator Project
# ------------------------
PLANT_TARGET = plant_app
PLANT_SRCS = main.cpp \
             BasePlant.cpp \
             PlantDecorator.cpp \
             GiftWrap.cpp \
             DecorativePot.cpp \
             SpecialArrangement.cpp
PLANT_OBJS = $(PLANT_SRCS:.cpp=.o)
PLANT_DEPS = Plant.h BasePlant.h PlantDecorator.h GiftWrap.h DecorativePot.h SpecialArrangement.h

# ------------------------
# Transaction Project
# ------------------------
TRANS_TARGET = transaction_app
TRANS_SRCS = main.cpp \
             Transaction.cpp \
             TransactionSnapshot.cpp \
             TransactionHistory.cpp \
             CreditCardPaymentStrategy.cpp \
             EWalletPaymentStrategy.cpp \
             EFTPaymentStrategy.cpp
TRANS_OBJS = $(TRANS_SRCS:.cpp=.o)

# ------------------------
# Default target
# ------------------------
all: $(PLANT_TARGET) $(TRANS_TARGET)

# ------------------------
# Plant Decorator build
# ------------------------
$(PLANT_TARGET): $(PLANT_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(PLANT_DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ------------------------
# Transaction build
# ------------------------
$(TRANS_TARGET): $(TRANS_OBJS)
	$(CXX) -std=c++11 -Wall -Wextra -o $@ $^

%.o: %.cpp
	$(CXX) -std=c++11 -Wall -Wextra -c $< -o $@

# ------------------------
# Clean build artifacts
# ------------------------
clean:
	rm -f $(PLANT_TARGET) $(TRANS_TARGET) *.o

# ------------------------
# Run targets
# ------------------------
run_plant: $(PLANT_TARGET)
	./$(PLANT_TARGET)

run_trans: $(TRANS_TARGET)
	./$(TRANS_TARGET)
