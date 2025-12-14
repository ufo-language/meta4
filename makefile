# Toolchain
CC       := clang
AR       := ar

# Flags
CFLAGS_DEBUG := -DDEBUG -std=c17 -Wall -Wextra -pedantic -g -O0
CFLAGS_SPEED := -DNDEBUG -std=c17 -Wall -O3 -ffast-math
CFLAGS_SIZE  := -DNDEBUG -std=c17 -Wall -Os
CFLAGS   := $(CFLAGS_DEBUG)
CPPFLAGS := -Isrc
LDFLAGS  := -flto

# Directories
SRCDIR   := src
TESTDIR  := tests
OBJDIR   := lib
BINDIR   := bin
UNITY_C  := $(OBJDIR)/unity_build.c
UNITY_O  := $(OBJDIR)/unity_build.o

LIBNAME  := libplx.a
LIBPATH  := $(OBJDIR)/$(LIBNAME)

# Source discovery
SRC_C    := $(shell find $(SRCDIR) -name '*.c' ! -name 'main.c')
MAIN_C   := $(SRCDIR)/main.c

# Test files
TEST_C   := $(wildcard $(TESTDIR)/*_test.c)
TEST_O   := $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/tests/%.o,$(TEST_C))
TEST_BIN := $(patsubst $(TESTDIR)/%.c,$(BINDIR)/%,$(TEST_C))

# Default target
all: $(LIBPATH) $(BINDIR)/plx $(TEST_BIN)

# Ensure directories exist
$(OBJDIR) $(BINDIR) $(OBJDIR)/tests:
	@mkdir -p $@

# ==============================
# Unity Build
# ==============================
# Optional: comment out UNITY build if you want normal per-file compilation

# $(UNITY_C): $(SRC_C) | $(OBJDIR)
# 	@echo "// Auto-generated unity build" > $@
# 	$(foreach f,$(SRC_C), \
# 	    echo '#include "'$(patsubst $(SRCDIR)/%,%,$f)'"' >> $@;)

# $(UNITY_O): $(UNITY_C) | $(OBJDIR)
# 	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# # Static library using unity build
# $(LIBPATH): $(UNITY_O)
# 	$(AR) rcs $@ $^

# ==============================
# Normal per-file compilation (disabled if UNITY used)
# ==============================
# Uncomment to disable unity build

SRC_O := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC_C))

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIBPATH): $(SRC_O)
	$(AR) rcs $@ $^

# ==============================
# Main executable
# ==============================
$(OBJDIR)/main.o: $(MAIN_C) | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BINDIR)/plx: $(OBJDIR)/main.o $(LIBPATH) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@

# ==============================
# Tests
# ==============================
$(OBJDIR)/tests/%.o: $(TESTDIR)/%.c | $(OBJDIR)/tests
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BINDIR)/%_test: $(OBJDIR)/tests/%_test.o $(LIBPATH) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@

# ==============================
# Dependencies
# ==============================
DEPS := $(OBJDIR)/main.d $(UNITY_O:.o=.d) $(TEST_O:.o=.d)
-include $(DEPS)

# ==============================
# Cleanup
# ==============================
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
