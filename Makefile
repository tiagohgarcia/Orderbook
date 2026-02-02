CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

SRC = src/OrderBook.cpp
TESTS = tests/TestMain.cpp tests/TestCancel.cpp tests/TestModify.cpp
BENCH = benchmarks/BenchOrderBook.cpp

TESTSFILE = test_order_book
BENCHFILE = bench_order_book

$(TESTSFILE): $(SRC) $(TESTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TESTSFILE)
	./$(TESTSFILE)


$(BENCHFILE): $(SRC) $(BENCH)
	$(CXX) -O3 -DNDEBUG $(CXXFLAGS) $^ -o $@

bench: $(BENCHFILE)
	./$(BENCHFILE)

clean:
	rm -f $(TESTSFILE)
	rm -f $(BENCHFILE)
