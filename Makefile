CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRC = src/OrderBook.cpp
TESTS = tests/TestMain.cpp tests/TestCancel.cpp

TARGET = test_order_book

all: $(TARGET)

$(TARGET): $(SRC) $(TESTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
