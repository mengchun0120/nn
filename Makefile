SRC_DIR=src
BIN_DIR=bin
TEST_DIR=test
TESTBIN_DIR=test/bin
LIBS=-lm
COMMON_FLAGS=-std=c++11 -Wall -fpic -I$(SRC_DIR) -L$(BIN_DIR)
DEBUG_FLAGS=-g $(COMMON_FLAGS)
RELEASE_FLAGS=-O3 $(COMMON_FLAGS) -DNDEBUG
MAIN_TASK=$(BIN_DIR)/libnn.so
OBJS=$(BIN_DIR)/group_list.o $(BIN_DIR)/types.o $(BIN_DIR)/node.o $(BIN_DIR)/edge.o \
	 $(BIN_DIR)/weight.o $(BIN_DIR)/act_func.o $(BIN_DIR)/output_model.o $(BIN_DIR)/neural_net.o
TEST_OBJS=$(TESTBIN_DIR)/test_group_list $(TESTBIN_DIR)/test_node $(TESTBIN_DIR)/test_neural_net

debug: CPPFLAGS=$(DEBUG_FLAGS)
debug: $(MAIN_TASK) $(TEST_OBJS) test

release: CPPFLAGS=$(RELEASE_FLAGS)
release: $(MAIN_TASK) $(TEST_OBJS) test

test: $(TEST_OBJS)
	./run_all_test.sh

$(MAIN_TASK): $(OBJS)
	g++ -shared $(CPPFLAGS) -o $@ $^ $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	g++ $(CPPFLAGS) -c -o $@ $<

$(TESTBIN_DIR)/%: $(TEST_DIR)/%.cpp $(OBJS)
	g++ $(DEBUG_FLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(MAIN_TASK) $(OBJS) $(TEST_OBJS)
