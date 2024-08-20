# Compilador e flags
CXX = g++
override CXXFLAGS += -g -Wall -Werror -std=c++17 -I$(REPL_PKG_DIR)/doctest `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -pthread

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Arquivos de código-fonte e cabeçalho
SRCS = $(shell find $(SRC_DIR) -type f -name '*.cpp' ! -name 'main.cpp')
HEADERS = $(shell find $(INCLUDE_DIR) -type f -name '*.hpp')

# Arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Arquivos de teste e objetos de teste
TEST_SRCS = $(shell find $(TEST_DIR) -type f -name '*.cpp')
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_EXEC = $(BIN_DIR)/test_program

# Executáveis
EXEC = $(BIN_DIR)/main

# Regra padrão
all: $(EXEC) $(TEST_EXEC)

# Regra para criar o executável principal
$(EXEC): $(OBJS) $(OBJ_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) $(OBJ_DIR)/main.o -o $(EXEC) $(LDFLAGS)
	@chmod +x $(EXEC)

# Regra para criar o executável de teste
$(TEST_EXEC): $(OBJS) $(TEST_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) $(TEST_OBJS) -o $(TEST_EXEC) $(LDFLAGS)
	@chmod +x $(TEST_EXEC)

# Regra para criar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Adiciona a regra para compilar main.cpp
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/main.cpp -o $@

# Regra de limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
