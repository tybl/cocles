TARGET := cocles
BLDDIR := build
OBJECTS = $(SOURCES:%.cpp=$(BLDDIR)/%.o)
DEPS = $(OBJECTS:.o=.d)
INCLUDES := -I src -I include
SOURCES := \
           src/ledger/internal/account.cpp \
           src/ledger/internal/Database.cpp \
           src/ledger/money.cpp \
           src/ledger/identifier.cpp \
           src/ledger/ledger.cpp \
           src/integer.cpp \
           src/decimal.cpp \

CXXFLAGS += -c -std=c++14 -MP -MMD -Werror
LFLAGS += -lpthread -lgmp

ifeq ($(CXX), clang++)
   CXXFLAGS += -Weverything -Wno-c++98-compat-pedantic -Wno-padded -stdlib=libc++
   LFLAGS += -lc++ -lc++abi
endif

ifeq ($(CXX), g++)
   CXXFLAGS += -Wall -Wextra
endif

.PHONY: all debug release check clean
all: debug

release: CXXFLAGS += -g0 -O3
release: $(TARGET)

debug: CXXFLAGS += -g3 -O0
debug: $(TARGET)

check: debug
	-./$(TARGET)

clean:
	$(RM) -r build $(TARGET)

$(TARGET): $(OBJECTS) $(BLDDIR)/src/main.o
	$(CXX) $(LFLAGS) $^ -o $@

$(BLDDIR):
	mkdir -p $(dir $(OBJECTS))

$(BLDDIR)/src/%.o: src/%.cpp | $(BLDDIR)
	$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) -o $@ $<

-include $(DEPS)
