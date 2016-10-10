CXX := clang++
TARGET := cocles
OBJECTS = $(SOURCES:src/%.cpp=$(BLDDIR)/src/%.o)
DEPS = $(OBJECTS:.o=.d)
INCLUDES := -I src -I include
SOURCES := \
           src/ledger/internal/account.cpp \
           src/ledger/internal/Database.cpp \
           src/ledger/money.cpp \
           src/ledger/identifier.cpp \
           src/ledger/ledger.cpp \
           src/decimal.cpp \

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

WARNINGS = -Werror -Weverything -Wno-c++98-compat-pedantic -Wno-padded
CFLAGS += -c -std=c++14 -stdlib=libc++ -MP -MMD
LFLAGS += -lc++ -lc++abi -lpthread -lgmp

.PHONY: all check clean
all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

clean:
	$(RM) -r build $(TARGET)

$(TARGET): $(OBJECTS) $(BLDDIR)/src/main.o
	$(CXX) $(LFLAGS) $^ -o $@

$(BLDDIR):
	mkdir -p $(dir $(OBJECTS))

$(BLDDIR)/src/%.o: src/%.cpp | $(BLDDIR)
	$(CXX) $(CFLAGS) $(WARNINGS) $(INCLUDES) -o $@ $<

-include $(DEPS)
