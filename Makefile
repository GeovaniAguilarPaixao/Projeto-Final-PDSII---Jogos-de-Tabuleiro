# Compilador e flags
CXX = g++
override CXXFLAGS += -g -Wall -Werror

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Arquivos de código-fonte e cabeçalho
SRCS = $(shell find $(SRC_DIR) -type f -name '*.cpp')
HEADERS = $(shell find $(INCLUDE_DIR) -type f -name '*.hpp')

# Arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executáveis
EXEC = $(BIN_DIR)/main.exe
EXEC_DEBUG = $(BIN_DIR)/main-debug

# Regra padrão
all: $(EXEC)

# Regra para criar executável
$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)
	@chmod +x $(EXEC)

# Regra para criar executável de debug
$(EXEC_DEBUG): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -U_FORTIFY_SOURCE -O0 $(OBJS) -o $(EXEC_DEBUG)
	@chmod +x $(EXEC_DEBUG)

# Regra para criar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra de debug
debug: $(EXEC_DEBUG)

# Regra de limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Regra de testes (opcional)
test:
	$(MAKE) -C $(TEST_DIR)

.PHONY: all clean debug test
