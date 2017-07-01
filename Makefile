SRC_DIR=core/src
INCLUDE_DIR=core/include
BIN_DIR=bin
UNIT_TEST_DIR=test/unit
UNIT_TEST_BIN_DIR=test/unit/bin
TEST_TOOL_DIR=test/tools/src
TEST_TOOL_INCLUDE_DIR=test/tools/include
TEST_TOOL_BIN_DIR=test/tools/bin
INTG_TEST_DIR=test/integration
INTG_TEST_BIN_DIR=test/integration/bin

LIBS=-lm
COMMON_FLAGS=-std=c++11 -Wall -fpic -I$(INCLUDE_DIR) -I$(TEST_TOOL_INCLUDE_DIR) -L$(BIN_DIR) -L$(TEST_TOOL_BIN_DIR)
DEBUG_FLAGS=-g $(COMMON_FLAGS)
RELEASE_FLAGS=-O3 $(COMMON_FLAGS) -DNDEBUG

COMMON_HEADER=$(INCLUDE_DIR)/common.hpp.gch
MAIN_TASK=$(BIN_DIR)/libnn.so
OBJS=$(BIN_DIR)/group.o $(BIN_DIR)/group_list.o $(BIN_DIR)/weight.o $(BIN_DIR)/batch.o \
	$(BIN_DIR)/act_func.o $(BIN_DIR)/node.o $(BIN_DIR)/edge.o $(BIN_DIR)/output_model.o \
	$(BIN_DIR)/neural_net.o $(BIN_DIR)/init_weight.o $(BIN_DIR)/eval.o $(BIN_DIR)/learn.o
UNIT_TEST_OBJS=$(UNIT_TEST_BIN_DIR)/test_group_list $(UNIT_TEST_BIN_DIR)/test_node \
	$(UNIT_TEST_BIN_DIR)/test_neural_net
TEST_TOOL_OBJS=$(TEST_TOOL_BIN_DIR)/simple_data_generator.o $(TEST_TOOL_BIN_DIR)/data_tools.o \
	$(TEST_TOOL_BIN_DIR)/config_parser.o
TEST_TOOL_TASK=$(TEST_TOOL_BIN_DIR)/libtool.so
INTG_TEST_OBJS=$(INTG_TEST_BIN_DIR)/gen_linear_data

debug: CPPFLAGS=$(DEBUG_FLAGS)
debug: $(COMMON_HEADER) $(MAIN_TASK) $(UNIT_TEST_OBJS) $(TEST_TOOL_TASK) $(INTG_TEST_OBJS)

release: CPPFLAGS=$(RELEASE_FLAGS)
release: $(COMMON_HEADER) $(MAIN_TASK) $(UNIT_TEST_OBJS) $(TEST_TOOL_TASK) $(INTG_TEST_OBJS)

init:
	./check_folder.sh

test: $(UNIT_TEST_OBJS)
	./run_all_unit_test.sh

$(COMMON_HEADER): $(INCLUDE_DIR)/common.hpp
	g++ $(CPPFLAGS) -c -o $@ $<

$(MAIN_TASK): $(OBJS)
	g++ -shared $(CPPFLAGS) -o $@ $^ $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp $(COMMON_HEADER)
	g++ $(CPPFLAGS) -c -o $@ $<

$(UNIT_TEST_BIN_DIR)/%: $(UNIT_TEST_DIR)/%.cpp $(MAIN_TASK)
	g++ $(DEBUG_FLAGS) -o $@ $< $(LIBS) -lnn

$(TEST_TOOL_BIN_DIR)/%.o: $(TEST_TOOL_DIR)/%.cpp $(TEST_TOOL_INCLUDE_DIR)/%.hpp $(MAIN_TASK)
	g++ $(CPPFLAGS) -c -o $@ $< -lnn

$(TEST_TOOL_TASK): $(TEST_TOOL_OBJS)
	g++ -shared $(CPPFLAGS) -o $@ $^ $(LIBS)

$(INTG_TEST_BIN_DIR)/%: $(INTG_TEST_DIR)/%.cpp $(MAIN_TASK) $(TEST_TOOL_TASK)
	g++ $(CPPFLAGS) -o $@ $< -ltool -lnn

clean:
	rm -f $(BIN_DIR)/* $(UNIT_TEST_BIN_DIR)/* $(TEST_TOOL_BIN_DIR)/* $(INTG_TEST_BIN_DIR)/*
