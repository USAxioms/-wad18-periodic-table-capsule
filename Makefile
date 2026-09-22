CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
DEBUG_FLAGS = -g -O0 -DDEBUG
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined

SOURCES = wad_fixed_point.c
HEADERS = wad_fixed_point.h periodic_table.h

.PHONY: all test unit debug sanitize clean verify help

all: test

# Unit tests
test: test_wad18_periodic
	./test_wad18_periodic

test_wad18_periodic: test_wad18_periodic.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o test_wad18_periodic test_wad18_periodic.c $(SOURCES)

# Debug build with sanitizers
debug: test_wad18_periodic_debug
	./test_wad18_periodic_debug

test_wad18_periodic_debug: test_wad18_periodic.c $(SOURCES) $(HEADERS)
	$(CC) $(DEBUG_FLAGS) $(SANITIZE_FLAGS) -o test_wad18_periodic_debug test_wad18_periodic.c $(SOURCES)

# Sanitizer testing
sanitize: test_wad18_periodic_sanitize
	./test_wad18_periodic_sanitize

test_wad18_periodic_sanitize: test_wad18_periodic.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -o test_wad18_periodic_sanitize test_wad18_periodic.c $(SOURCES)

# Verify reproducibility
verify: test
	@echo "=== Cross-Platform Reproducibility Check ==="
	@echo "Platform: $$(uname -s) $$(uname -m)"
	@echo "Compiler: $$($(CC) --version | head -1)"
	@echo "Status: PASS (if test succeeded above)"
	@echo ""
	@echo "To verify on multiple platforms:"
	@echo "  ./test_cross_platform.sh"

# Clean build artifacts
clean:
	rm -f test_wad18_periodic test_wad18_periodic_debug test_wad18_periodic_sanitize
	rm -f *.o *.a *.so
	rm -f vgcore.*
	rm -f ./*.pyc

# Help
help:
	@echo "WAD18 Periodic Table - Reproducibility Capsule"
	@echo ""
	@echo "Targets:"
	@echo "  make all       - Build and run tests (default)"
	@echo "  make test      - Run unit tests"
	@echo "  make debug     - Build with debug symbols and run"
	@echo "  make sanitize  - Build with AddressSanitizer and UBSan"
	@echo "  make verify    - Verify reproducibility on this platform"
	@echo "  make clean     - Remove build artifacts"
	@echo "  make help      - Show this message"
	@echo ""
	@echo "Expected behavior:"
	@echo "  ✅ All tests pass"
	@echo "  ✅ Identical output on multiple runs"
	@echo "  ✅ No memory errors (with sanitize)"
	@echo "  ✅ No platform-dependent behavior"
