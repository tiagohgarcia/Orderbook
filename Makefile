CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra	

SRC = src/order_book.cpp
TESTS = tests/test_main.cpp tests/test_cancel.cpp tests/test_modify.cpp
BENCH = benchmarks/bench_order_book.cpp

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
