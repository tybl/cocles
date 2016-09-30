CXX := clang++
TARGET := cocles
TEST_TRGT = cocles-test
OBJECTS = $(SOURCES:src/%.cpp=$(BLDDIR)/src/%.o)
TEST_OBJ = $(TEST_SRC:test/%.cpp=$(BLDDIR)/test/%.o)
DEPS = $(OBJECTS:.o=.d)
INCLUDES := -I src -I include
SOURCES := src/ledger/internal/account.cpp \
           src/ledger/internal/account_table.cpp \
           src/ledger/internal/adjustment.cpp \
           src/ledger/internal/adjustment_table.cpp \
           src/ledger/money.cpp \
           src/ledger/identifier.cpp \
           src/ledger/ledger.cpp

TEST_SRC := test/identifier-test.cpp

ifndef CONFIG
   CONFIG=Valgrind
endif

ifeq ($(CONFIG), AddSan)
   BLDDIR := build/sanitize
   CFLAGS := -g3 -O0 -fsanitize=address
   LFLAGS := -g3 -O0 -fsanitize=address
endif

ifeq ($(CONFIG), Valgrind)
   BLDDIR := build/debug
   CFLAGS := -g3 -O0
   LFLAGS := -g3 -O0
endif

ifeq ($(CONFIG), Release)
   BLDDIR := build/release
   CFLAGS := -g0 -O3
   LFLAGS := -g0 -O3
endif

WARNINGS = -pedantic -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
CFLAGS += -c -std=c++14 -stdlib=libc++ -MP -MMD
LFLAGS += -lc++ -lc++abi -lpthread -lgmp

.PHONY: all test clean
all: $(TARGET)

test: $(TEST_TRGT)
	./$(TEST_TRGT)

clean:
	$(RM) -r build $(TARGET) $(TEST_TRGT)

$(TARGET): $(OBJECTS) $(BLDDIR)/src/main.o
	$(CXX) $(LFLAGS) $^ -o $@

$(TEST_TRGT): $(OBJECTS) $(TEST_OBJ) lib/gtest_main.a
	$(CXX) $(LFLAGS) $^ -o $@

$(BLDDIR):
	mkdir -p $(dir $(OBJECTS))
	mkdir -p $(dir $(TEST_OBJ))

$(BLDDIR)/src/%.o: src/%.cpp | $(BLDDIR)
	$(CXX) $(CFLAGS) $(WARNINGS) $(INCLUDES) -o $@ $<

$(BLDDIR)/test/%.o: test/%.cpp | $(BLDDIR)
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $<

-include $(DEPS)
