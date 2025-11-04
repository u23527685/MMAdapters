# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17
DEBUGFLAGS := -g
COVERAGEFLAGS := -fprofile-arcs -ftest-coverage

# Sources
TEST_MAIN := TestingMain.cpp
DEMO_MAIN := DemoMain.cpp
COMMON_SOURCES := $(filter-out $(TEST_MAIN) $(DEMO_MAIN), $(wildcard *.cpp))
TEST_OBJECTS := $(COMMON_SOURCES:.cpp=.o) $(TEST_MAIN:.cpp=.o)
DEMO_OBJECTS := $(COMMON_SOURCES:.cpp=.o) $(DEMO_MAIN:.cpp=.o)

# Targets
TEST_TARGET := test
DEMO_TARGET := Demo

# Default build
all: $(TEST_TARGET)

# Build test main
$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# Build demo main
$(DEMO_TARGET): $(DEMO_OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# Object compilation rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build with -g
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(TEST_TARGET)
	@echo "Built with debug symbols."

# Build with coverage flags
coverage: CXXFLAGS += $(COVERAGEFLAGS)
coverage: LDFLAGS += $(COVERAGEFLAGS) -lgcov
coverage: clean $(TEST_TARGET)
	@echo "Built with coverage flags (including gcov)."

# Run the test program
run: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run the demo program
run-demo: $(DEMO_TARGET)
	./$(DEMO_TARGET)

# Run with gdb
gdb: debug
	gdb ./$(TEST_TARGET)

# Run with valgrind
valgrind: debug
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TEST_TARGET)

# Generate coverage report (after running the program built with 'make coverage')
gcov-report:
	gcov $(COMMON_SOURCES) $(TEST_MAIN)

# Generate HTML coverage report using gcovr
coverage-html:
	@echo "Generating HTML coverage report..."
	@if command -v gcovr >/dev/null 2>&1; then \
		mkdir -p coverage_html; \
		gcovr --html-details coverage_html/index.html --root . --exclude-directories 'tests|external'; \
		echo "HTML report generated in coverage_html/index.html"; \
	else \
		echo "Error: gcovr not found. Install it with: pip install gcovr"; \
		exit 1; \
	fi


# Alternative: Generate HTML coverage report using lcov
coverage-html-lcov:
	@echo "Generating HTML coverage report with lcov..."
	@if command -v lcov >/dev/null 2>&1 && command -v genhtml >/dev/null 2>&1; then \
		lcov --capture --directory . --output-file coverage.info; \
		lcov --remove coverage.info '/usr/*' --output-file coverage.info; \
		genhtml coverage.info --output-directory coverage_html; \
		echo "HTML report generated in coverage_html/index.html"; \
	else \
		echo "Error: lcov/genhtml not found. Install with: sudo apt-get install lcov"; \
		exit 1; \
	fi

# Clean only coverage HTML report
clean-html:
	rm -f coverage*.html coverage*.css
	rm -rf coverage_html

# Cleanup
clean:
	rm -f $(COMMON_SOURCES:.cpp=.o) $(TEST_TARGET) $(DEMO_TARGET) *.gcda *.gcno *.gcov coverage*.html coverage*.css coverage.info
	rm -rf coverage_html
