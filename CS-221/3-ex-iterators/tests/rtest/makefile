# Contains library utilities designed to
# be portable between different assignment
# test suites
RTEST_UTILS_DIR?=$(RTEST_PATH)/utils
RTEST_INCLUDE_DIR?=$(RTEST_PATH)/include

RTEST_DEBUG_FLAGS := -DDEBUG -g

RTEST_CFLAGS :=
RTEST_CFLAGS += -std=c++17
RTEST_CFLAGS += -Wall -pedantic
# We test self/move or assignment
# On MacOS CXX is aliased to g++. Although clang is used under the hood, 
# this disables warnings for self-assignment
ifeq ($(UNAME_S),Darwin) 
	RTEST_CFLAGS += -Wno-self-assign-overloaded -Wno-self-move
endif

RTEST_CFLAGS += $(RTEST_DEBUG_FLAGS)

RTEST_CFLAGS += -I$(RTEST_INCLUDE_DIR) 
RTEST_CFLAGS += -I$(RTEST_ASSIGNMENT_INCLUDE_DIR)
RTEST_CFLAGS += -I$(RTEST_SRC_DIR)

# Add more assignment specific utilities here
# Although this will break when linking. Only include here if they are universally needed


RTEST_UTILS_OBJS := memhook.o
RTEST_UTILS_OBJS += xoshiro256.o
RTEST_UTILS_OBJS += typegen.o
RTEST_UTILS_OBJS += assertions.o

##########################################################################################

CXX?=g++
CFLAGS ?= $(RTEST_CFLAGS)
SRC_EXT:=%.cpp %.cc %.cxx
LDFLAGS ?=

_RTEST_STD_BUILD=$(CXX) $(CFLAGS) $(EXTRA_CXXFLAGS) $(filter $(SRC_EXT) %.o, $^) -o $@
RTEST_STD_BUILD=$(_RTEST_STD_BUILD) $(LDFLAGS)
RTEST_STD_COMPILE=$(_RTEST_STD_BUILD) -c

## UTILS ##

RTEST_INCLUDE_HEADERS := $(wildcard $(RTEST_INCLUDE_DIR)/*.h)
RTEST_UTILS_OBJS := $(patsubst %,$(RTEST_UTILS_DIR)/%, $(RTEST_UTILS_OBJS))

## TESTS ##

RTEST_TESTS_SRCS := $(wildcard $(RTEST_TEST_DIR)/*.cpp)
RTEST_TESTS := $(patsubst $(RTEST_TEST_DIR)/%.cpp, %, $(RTEST_TESTS_SRCS))

## SRC ##

RTEST_SRC_HEADERS = $(wildcard $(RTEST_SRC_DIR)/*.h)
RTEST_SRC_OBJS := $(patsubst %.cpp, %.o, $(wildcard $(RTEST_SRC_DIR)/*.cpp))
# Ignore main.cpp
RTEST_SRC_OBJS := $(filter-out $(RTEST_SRC_DIR)/main.o, $(RTEST_SRC_OBJS))

RTEST_EXES = $(patsubst %, $(RTEST_BUILD_DIR)/%, $(RTEST_TESTS))

## ASSIGNMENT ##

RTEST_ASSIGNMENT_INCLUDE_HEADERS := $(wildcard  $(RTEST_ASSIGNMENT_INCLUDE_DIR)/*.h)
RTEST_ASSIGNMENT_OBJS := $(patsubst %, $(RTEST_ASSIGNMENT_UTILS_DIR)/%, $(RTEST_ASSIGNMENT_OBJS))

## BUILD ##

RTEST_OBJECTS := $(RTEST_SRC_OBJS)
RTEST_OBJECTS += $(RTEST_UTILS_OBJS)
RTEST_OBJECTS += $(RTEST_ASSIGNMENT_OBJS)

RTEST_HEADERS := $(RTEST_SRC_HEADERS)
RTEST_HEADERS += $(RTEST_INCLUDE_HEADERS)
RTEST_HEADERS += $(RTEST_ASSIGNMENT_INCLUDE_HEADERS)

build-all: $(RTEST_EXES)

$(RTEST_BUILD_DIR):
	$(shell mkdir -p $(RTEST_BUILD_DIR))

list:
	@echo $(RTEST_TESTS)
.PHONY: list

%.o: %.cpp
	$(RTEST_STD_COMPILE)

RTEST_RUN_CMDS := $(patsubst %, run/%, $(RTEST_TESTS))

run/%: $(RTEST_BUILD_DIR)/%
	@$(patsubst run/%, ./$(RTEST_BUILD_DIR)/%, $@)

run-all: $(RTEST_RUN_CMDS)

clean:
	$(RM) $(RTEST_EXES) $(RTEST_OBJECTS)
	$(shell $(RM) -rf $(RTEST_BUILD_DIR))
.PHONY: clean

## ASSIGNMENT-SPECIFIC BUILD PROCESSES ##

$(RTEST_BUILD_DIR)/%: $(RTEST_TEST_DIR)/%.cpp $(RTEST_OBJECTS) $(RTEST_HEADERS) $(RTEST_BUILD_DIR)
	$(RTEST_STD_BUILD)
