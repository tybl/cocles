CC := clang++
TARGET := cocles
OBJECTS = $(SOURCES:src/%.cpp=$(BLDDIR)/%.o)
DEPS = $(OBJECTS:.o=.d)
INCLUDES := -I src -I include
SOURCES := src/main.cpp \
	   src/account_table.cpp \
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

CFLAGS += -c -std=c++14 -stdlib=libc++ -pedantic -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-documentation-unknown-command -Wno-documentation -Wno-exit-time-destructors -MP -MMD
LFLAGS += -lc++ -lc++abi

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o $@

$(BLDDIR):
	mkdir -p $(dir $(OBJECTS))

$(BLDDIR)/%.o: src/%.cpp | $(BLDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

.PHONY: clean
clean:
	$(RM) -r build $(TARGET)

-include $(DEPS)
