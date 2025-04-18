# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
IMGUI_DIR := deps/imgui
BACKENDS_DIR := $(IMGUI_DIR)/backends

IMGUI_SRCS := \
	$(IMGUI_DIR)/imgui.cpp \
	$(IMGUI_DIR)/imgui_draw.cpp \
	$(IMGUI_DIR)/imgui_tables.cpp \
	$(IMGUI_DIR)/imgui_widgets.cpp \
	$(BACKENDS_DIR)/imgui_impl_sdl2.cpp \
	$(BACKENDS_DIR)/imgui_impl_opengl3.cpp

# Source files and output
SRCS := $(shell find $(SRC_DIR) -name '*.cpp') $(IMGUI_SRCS)
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

# Include flags for each subdir in include/ and imgui/
INC_PATHS := $(shell find $(INC_DIR) -type d) $(IMGUI_DIR) $(BACKENDS_DIR)
INC_FLAGS := $(addprefix -I, $(INC_PATHS)) $(shell sdl2-config --cflags)

# Compiler and flags
CXX := g++
DEP_FLAGS = -MMD -MP -MF $(@:.o=.d)
CXXFLAGS := -std=c++17 -Wall -g -c $(INC_FLAGS)
LDFLAGS := -lSDL2 -lSDL2_ttf -lGLEW -lGL

TARGET := polygine

.PHONY: all clean

# Default rule
all: $(TARGET)

# Link objects to create the final executable
$(TARGET): $(OBJS)
	@echo "Linking $@..."
	@$(CXX) $^ -o $@ $(LDFLAGS)

# Compile source files to objects
$(BUILD_DIR)/%.o: %.cpp makefile
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	$(CXX) $(CXXFLAGS) $(DEP_FLAGS) $< -o $@

-include $(DEPS)

# Clean up build files
clean:
	rm -rf $(TARGET) $(BUILD_DIR) imgui.ini

print-i:
	@echo $(DEPS)