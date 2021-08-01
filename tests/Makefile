BIN_NAME = tests

SRC_FILES = common.cpp math.cpp string.cpp
OBJ_FILES = $(addsuffix .o,$(basename $(SRC_FILES)))

INCLUDE_DIRS = -I$(GTEST_DIR)/googletest/include \
			   -I../include

LIB_DIRS = -L$(GTEST_DIR)/lib

LIBS = -lgtest -lgtest_main -lpthread

$(BIN_NAME): $(OBJ_FILES)
	$(CXX) $^ $(LIB_DIRS) $(LIBS) -o $@

%.o: %.cpp
	$(CXX) -std=c++2a $(INCLUDE_DIRS) -c $^ -o $@

.PHONY: all clean build rebuild

all: build
build: $(BIN_NAME)
rebuild: clean build
clean:
	rm -rf *.o $(BIN_NAME)