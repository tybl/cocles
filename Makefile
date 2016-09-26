CXX := clang++
TARGET := cocles
OBJECTS = $(SOURCES:src/%.cpp=$(BLDDIR)/%.o)
DEPS = $(OBJECTS:.o=.d)
INCLUDES := -I src -I include
SOURCES := src/main.cpp \
           src/account_table.cpp \
           src/adjustment_table.cpp \
           src/amount.cpp \
           src/identifier.cpp \
           src/ledger.cpp

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

CFLAGS += -c -std=c++14 -stdlib=libc++ -pedantic -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -MP -MMD
LFLAGS += -lc++ -lc++abi

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LFLAGS) -o $@

$(BLDDIR):
	mkdir -p $(dir $(OBJECTS))

$(BLDDIR)/%.o: src/%.cpp | $(BLDDIR)
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $<

.PHONY: clean
clean:
	$(RM) -r build $(TARGET)

-include $(DEPS)
