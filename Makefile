SRC_DIR=src
BIN_DIR=bin
TEST_DIR=test
TESTBIN_DIR=test/bin
LIBS=-lgsl -lgslcblas -lm
COMMON_FLAGS=-std=c++11 -Wall -I$(SRC_DIR) -DHAVE_INLINE
DEBUG_FLAGS=-g $(COMMON_FLAGS)
RELEASE_FLAGS=-O3 $(COMMON_CFLAGS) -DGSL_RANGE_CHECK_OFF -DNDEBUG
MAIN_TASK=$(BIN_DIR)/nn
OBJS=$(BIN_DIR)/node.o $(BIN_DIR)/weight.o $(BIN_DIR)/edge.o \
	 $(BIN_DIR)/act_func.o $(BIN_DIR)/output_model.o $(BIN_DIR)/neural_net.o
TEST_OBJS=$(TESTBIN_DIR)/test_node $(TESTBIN_DIR)/test_neural_net

debug: CPPFLAGS=$(DEBUG_FLAGS)
debug: $(MAIN_TASK) $(TEST_OBJS)

release: CPPFLAGS=$(RELEASE_FLAGS)
release: $(MAIN_TASK) $(TEST_OBJS)

test: $(TEST_OBJS)
	./run_all_test.sh

$(MAIN_TASK): $(SRC_DIR)/main.cpp $(OBJS)
	g++ $(CPPFLAGS) -o $@ $^ $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	g++ $(CPPFLAGS) -c -o $@ $<

$(TESTBIN_DIR)/%: $(TEST_DIR)/%.cpp $(OBJS)
	g++ $(CPPFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(MAIN_TASK) $(OBJS) $(TEST_OBJS)
