# Variáveis
CXX = g++
CXXFLAGS = -std=c++20 -fPIC
LDFLAGS = -shared

# Arquivos fonte e objetos
SRC = ./src/mutex.cpp
OBJ = mutex.o
LIB = ./lib/libmutex.so

# Arquivos de exemplo
EXAMPLE1_SRC = ./example/thread_race_cond_lamport.cpp
EXAMPLE1_OUT = ./build/thread_race_cond_lamport
EXAMPLE2_SRC = ./example/thread_race_cond_pthread.cpp
EXAMPLE2_OUT = ./build/thread_race_cond_pthread

# Regra padrão
all: directories $(EXAMPLE1_OUT) $(EXAMPLE2_OUT) post_compile

# Regra para criar os diretórios
.PHONY: directories
directories:
	mkdir -p build lib

# Regra para compilar o arquivo objeto
$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para criar a biblioteca
$(LIB): $(OBJ)
	$(CXX) $(LDFLAGS) $< -o $@

# Regra para compilar os arquivos de exemplo
$(EXAMPLE1_OUT): $(EXAMPLE1_SRC) $(LIB)
	$(CXX) -L ./lib $< -o $@ -lmutex

$(EXAMPLE2_OUT): $(EXAMPLE2_SRC)
	$(CXX) $< -o $@ -lpthread

# Regra para limpar os arquivos compilados
clean:
	rm -f $(OBJ) $(EXAMPLE1_OUT) $(EXAMPLE2_OUT) $(LIB)
	rm -rf build lib

# Regra para remover o arquivo objeto após a compilação
.PHONY: post_compile
post_compile:
	rm -f $(OBJ)