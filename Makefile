CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra	
CXXFLAGSASAN = -O0 -g -fno-omit-frame-pointer -fsanitize=address,undefined

SRC = src/order_book.cpp src/price_level.cpp
TESTS = tests/test_main.cpp tests/test_cancel.cpp tests/test_modify.cpp
BENCH = benchmarks/bench_order_book.cpp

TESTSFILE = test_order_book
TESTSASAN = test_asan
BENCHFILE = bench_order_book

$(TESTSFILE): $(SRC) $(TESTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TESTSFILE)
	./$(TESTSFILE)
	

$(TESTSASAN): $(SRC) $(TESTS)
	$(CXX) $(CXXFLAGS) $(CXXFLAGSASAN) $^ -o $@

testAsan: $(TESTSASAN)
	./$(TESTSASAN)


$(BENCHFILE): $(SRC) $(BENCH)
	$(CXX) -O3 -DNDEBUG $(CXXFLAGS) $^ -o $@

bench: $(BENCHFILE)
	./$(BENCHFILE)

clean:
	rm -f $(TESTSFILE) $(TESTSASAN) $(BENCHFILE)
