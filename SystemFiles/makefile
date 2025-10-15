# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17
DEBUGFLAGS := -g
COVERAGEFLAGS := -fprofile-arcs -ftest-coverage

# All .cpp files in the directory
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

# Output executable
TARGET := stafftest1

# Default build
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build with -g
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)
	@echo "Built with debug symbols."

# Build with coverage flags
coverage: CXXFLAGS += $(COVERAGEFLAGS)
coverage: LDFLAGS += $(COVERAGEFLAGS)
coverage: clean $(TARGET)
	@echo "Built with coverage flags."

# Run the program
run: $(TARGET)
	./$(TARGET)

# Run with gdb
gdb: debug
	gdb ./$(TARGET)

# Run with valgrind
valgrind: debug
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET)

# Generate coverage report (after running the program built with 'make coverage')
gcov-report:
	gcov $(SOURCES)

# Generate HTML coverage report using gcovr
coverage-html:
	@echo "Generating HTML coverage report..."
	@if command -v gcovr >/dev/null 2>&1; then \
		gcovr --html-details -o coverage.html --root .; \
		echo "HTML report generated: coverage.html"; \
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
	rm -f $(OBJECTS) $(TARGET) *.gcda *.gcno *.gcov coverage*.html coverage*.css coverage.info
	rm -rf coverage_html