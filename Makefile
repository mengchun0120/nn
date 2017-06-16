SRC_DIR=src
BIN_DIR=build
TEST_DIR=test
LIBS=-lgsl -lgslcblas -lm
COMMON_FLAGS=-std=c++11 -Wall -I$(SRC_DIR) -DHAVE_INLINE
DEBUG_FLAGS=-g $(COMMON_FLAGS)
RELEASE_FLAGS=-O3 $(COMMON_CFLAGS) -DGSL_RANGE_CHECK_OFF -DNDEBUG
MAIN_TASK=$(BIN_DIR)/nn
OBJS=$(BIN_DIR)/node.o $(BIN_DIR)/weight.o $(BIN_DIR)/types.o \
	 $(BIN_DIR)/act_func.o $(BIN_DIR)/output_func.o $(BIN_DIR)/neural_net.o
TEST_OBJS=

debug: CPPFLAGS=$(DEBUG_FLAGS)
debug: $(MAIN_TASK) $(TEST_OBJS)

release: CPPFLAGS=$(RELEASE_FLAGS)
release: $(MAIN_TASK) $(TEST_OBJS)

$(MAIN_TASK): $(SRC_DIR)/main.cpp $(OBJS)
	g++ $(CPPFLAGS) -o $@ $^ $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	g++ $(CPPFLAGS) -c -o $@ $<

$(TEST_DIR)/%: $(TEST_DIR)/%.cpp $(OBJS)
	g++ $(CPPFLAGS) -o $@ $^ $(LIBS)
	$@

clean:
	rm -f $(MAIN_TASK) $(OBJS) $(TEST_OBJS)
