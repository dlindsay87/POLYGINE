CXX = gcc
CXXFLAGS = -std=gnu99 -Wall

COMPFLAGS = -g -c -fPIC -Dflecs_EXPORTS
LINKFLAGS = -shared -o

TARGET = libflecs.so

all: $(TARGET)

$(TARGET): build/flecs.o
	$(CXX) $(LINKFLAGS) $@ $^

build/flecs.o: distr/flecs.c distr/flecs.h
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(COMPFLAGS) $< -o $@
