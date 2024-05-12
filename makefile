### TODO ###

# PLEASE REFER TO YOUR SYSTEM FOR LIBRARY DEPS
# ADJUST FIND FOR COMPATABILITY
# ADJUST SLASHES FOR COMPATABILITY

# debug: CXXFLAGS += -g -O0 -U_FORTIFY_SOURCE

CXX = g++

SRC_DIR := src
OBJ_DIR := obj
DEP_DIR := deps
LIB_DIR := lib/polygine

CXXFLAGS := -std=c++14 -Werror -Wall
DEP_FLAGS := -MMD -MP
LIB_FLAGS := -lsdl2 -lglew -framework opengl

define get_objs
	$(eval $@_CPPS := $(shell find $(1) -name '*.cpp')) 
	$(2) := $(patsubst $(1)%.cpp,$(OBJ_DIR)/$(1)%.o,$($@_CPPS))
endef

define get_deps
	$(eval $@_CPPS := $(shell find $(1) -name '*.cpp'))
	$(2) := $(patsubst $(1)%.cpp,$(DEP_DIR)/$(1)%.d,$($@_CPPS)) 
endef

$(eval $(call get_objs,$(SRC_DIR),SRC_OBJS))
$(eval $(call get_objs,$(LIB_DIR),LIB_OBJS))

$(eval $(call get_deps,$(SRC_DIR),SRC_DEPS))
$(eval $(call get_deps,$(LIB_DIR),LIB_DEPS))

LIB_UNITY := $(LIB_DIR)/polygine.h

TARGET_MAIN := main
TARGET_LIB := lib/libpolygine.a

.PHONY: all lib debug clean

all: lib game
game: $(TARGET_MAIN)
lib: $(TARGET_LIB)

$(LIB_UNITY): $(shell find $(LIB_DIR)/**/* -name '*.h')
	@echo "#pragma once\n" > $@
	@$(foreach header,$^,echo '#include $(subst $(LIB_DIR)/,,"$(header)")' >> $@;)
	@echo "We have made $(LIB_UNITY) unity file!"

$(TARGET_LIB): $(LIB_OBJS)
	@echo "Compiling $@ library..."
	@ar rcs $@ $^
	@echo "We have made $(TARGET_LIB) library!"

-include $(LIB_DEPS)
$(OBJ_DIR)/$(LIB_DIR)/%.o: $(LIB_DIR)/%.cpp makefile
	@echo "Compiling $@ lib object..."
	@mkdir -p $(@D)
	@mkdir -p $(DEP_DIR)/$(dir $<)
	@$(CXX) $(CXXFLAGS) -I$(LIB_DIR) $(DEP_FLAGS) -MF $(DEP_DIR)/$(basename $<).d -c $< -o $@

$(TARGET_MAIN): $(TARGET_LIB) $(SRC_OBJS) 
	@echo "Compiling $@ executable..."
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LIB_FLAGS)
	@echo "We have made $(TARGET_MAIN)!"

-include $(SRC_DEPS)
$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(LIB_UNITY) makefile
	@echo "Compiling $@ object..."
	@mkdir -p $(@D)
	@mkdir -p $(DEP_DIR)/$(<D)
	@$(CXX) $(CXXFLAGS) -I$(LIB_DIR) -I$(SRC_DIR) $(DEP_FLAGS) -MF $(DEP_DIR)/$(basename $<).d -c $< -o $@

clean:
	@rm -rf $(TARGET_MAIN) $(LIB_UNITY) {$(OBJ_DIR),$(DEP_DIR)}/$(SRC_DIR)
	@echo "Cleaned game."

clean-lib:
	@rm -rf $(TARGET_LIB) $(LIB_UNITY) {$(OBJ_DIR),$(DEP_DIR)}/$(LIB_DIR)
	@echo "Cleaned library."

clean-all:
	@make clean && make clean-lib
	@rm -rf $(OBJ_DIR) $(DEP_DIR)

print-%  : ; @echo $* = $($*)
