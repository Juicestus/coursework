# Include the TA configuration if it exists
-include ta_config

RTEST_PATH := rtest

# Build directory
RTEST_BUILD_DIR := build
# Contain sources for tests
RTEST_TEST_DIR := tests
# Source directory
RTEST_SRC_DIR ?= ../src

# Specific to the current assignment
RTEST_ASSIGNMENT_INCLUDE_DIR ?= include
RTEST_ASSIGNMENT_UTILS_DIR ?= utils

# Add more assignment specific utilities here
# Although this will break when linking. Only include here if they are universally needed
RTEST_ASSIGNMENT_OBJS := sample-graphs.o graph-assert.o

all: run-all

include ./rtest/makefile
