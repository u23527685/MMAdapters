CXX = g++
CXXFLAGS = -Wall -g

TARGET = main

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
       SpecialArrangement.cpp \
  

OBJS = $(SRCS:.cpp=.o)

DEPS = Transaction.h TransactionSnapshot.h TransactionHistory.h \
       CreditCardPaymentStrategy.h EWalletPaymentStrategy.h EFTPaymentStrategy.h \
       Plant.h BasePlant.h PlantDecorator.h GiftWrap.h DecorativePot.h SpecialArrangement.h \
       AddStock.h RemoveStock.h PlantStock.h PlantInventory.h InventoryObserver.h \
       StaffObserver.h SalesFloorObserver.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o *.gcda *.gcno *.gcov

run: $(TARGET)
	./$(TARGET)

coverage: CXXFLAGS += --coverage
coverage: clean $(TARGET)
	./$(TARGET)
	gcov $(SRCS)
