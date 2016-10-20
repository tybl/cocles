TARGET := cocles
BLDDIR := build
SOURCES := \
           src/ledger/internal/account.cpp \
           src/ledger/internal/Database.cpp \
           src/ledger/money.cpp \
           src/ledger/identifier.cpp \
           src/ledger/ledger.cpp \
           src/main.cpp \

CPPFLAGS += -c -MP -MMD -Werror -I src -I include
CXXFLAGS += -std=c++14
LFLAGS += -lpthread -lgmp
OBJECTS = $(SOURCES:%.cpp=$(BLDDIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

ifeq ($(CXX), clang++)
   CPPFLAGS += -Weverything
   CXXFLAGS += -Wno-c++98-compat-pedantic -Wno-padded -stdlib=libc++
   LFLAGS += -lc++ -lc++abi
endif

ifeq ($(CXX), g++)
   CXXFLAGS += -Wall -Wextra
endif

.PHONY: all debug release check clean
all: debug

release: CPPFLAGS += -g0 -O3 -D NDEBUG -D DOCTEST_CONFIG_DISABLE
release: LFLAGS += -flto
release: $(TARGET)

debug: CPPFLAGS += -g3 -O0
debug: $(TARGET)

check: debug
	-./$(TARGET)

clean:
	$(RM) -r $(BLDDIR) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LFLAGS) $^ -o $@

$(BLDDIR):
	mkdir -p $(dir $(OBJECTS))

$(BLDDIR)/%.o: %.cpp | $(BLDDIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

-include $(DEPS)
