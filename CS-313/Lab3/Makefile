CC=gcc
CCFLAGS=-ggdb3 -Og -fsanitize=undefined -Wall -Wextra -Wpedantic -Wconversion -Werror -fanalyzer

LIBSRC=threading.c threading_data.c
LIBPATH=$(shell pwd)
LIB=libthreading.so

INCLPATH=$(shell pwd)
INCL=threading.h

APPSRC=main.c
APP=main

all: lib app

.PHONY: lib
lib: CCFLAGS+=-shared -fPIC
lib: $(LIB)

$(LIB): $(LIBSRC)
	$(CC) -I$(INCLPATH) $(CCFLAGS) $(LIBSRC) -o $@

.PHONY: app
app: $(APP)

$(APP): $(APPSRC)
	$(CC) -I$(INCLPATH) -L$(LIBPATH) $(CCFLAGS) $< -Wl,-rpath=$(LIBPATH) -lthreading -o $@

.PHONY: clean
clean:
	rm -rf $(APP) $(LIB)
