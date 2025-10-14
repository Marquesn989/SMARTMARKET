# SmartMarket - Makefile (VS Code + raylib externo)
# Compiladores e flags
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c99 -D_DEFAULT_SOURCE
CXXFLAGS = -Wall -Wextra -std=c++17 -D_DEFAULT_SOURCE

# Caminho do raylib externo (reutiliza o que já está em C:/Users/a35560/SmartMarket/raylib)
# Use barras normais (/) para evitar problemas de escape no MinGW.
RAYLIB_DIR ?= C:/Users/a35560/SmartMarket/raylib

# Diretórios
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
OBJ_DIR_WIN = $(BUILD_DIR)\\obj
INCLUDE_PATH = -I$(RAYLIB_DIR)/include
LIBRARY_PATH = -L$(RAYLIB_DIR)/lib

# Bibliotecas
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Fontes
SOURCES_C = $(wildcard $(SRC_DIR)/*.c)
SOURCES_CPP = $(wildcard $(SRC_DIR)/*.cpp)

# Se existir main.cpp, exclui main.c para evitar múltiplas definições de main
ifeq ($(wildcard $(SRC_DIR)/main.cpp),$(SRC_DIR)/main.cpp)
  SOURCES_C := $(filter-out $(SRC_DIR)/main.c,$(SOURCES_C))
endif

OBJS_C = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES_C))
OBJS_CPP = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES_CPP))
OBJS = $(OBJS_C) $(OBJS_CPP)

EXECUTABLE = $(BUILD_DIR)/smartmarket.exe

# Escolhe o linker: usa C++ se houver objetos C++
LINKER = $(if $(strip $(OBJS_CPP)),$(CXX),$(CC))

# Regra principal
all: $(EXECUTABLE)

# Linkagem
$(EXECUTABLE): $(OBJS) | $(BUILD_DIR)
	$(LINKER) $(OBJS) -o $(EXECUTABLE) $(LIBRARY_PATH) $(LIBS)
	@rem Copiar raylib.dll ao lado do executável para evitar problemas de PATH
	@if exist "$(RAYLIB_DIR)\lib\raylib.dll" cmd /c copy /Y "$(RAYLIB_DIR)\lib\raylib.dll" "$(BUILD_DIR)" >nul

# Compilação C
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $@

# Compilação C++
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

# Diretórios
$(BUILD_DIR):
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
$(OBJ_DIR):
	@if not exist $(OBJ_DIR_WIN) mkdir $(OBJ_DIR_WIN)

# Executar o programa
run: $(EXECUTABLE)
	set PATH=$(RAYLIB_DIR)/lib;$$PATH && $(EXECUTABLE)

# Limpar arquivos compilados
clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

# Rebuild completo
rebuild: clean all

.PHONY: all run clean rebuild
