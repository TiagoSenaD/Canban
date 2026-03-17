# Variáveis de compilação
CC = clang
CFLAGS = -Wall -Wextra -fPIC -I./include
LDFLAGS = -shared

TARGET_DIR = ../../../build
TARGET = $(TARGET_DIR)/libkanban.so

SRC = kanban.c
OBJ = $(SRC:.c=.o)

.INTERMEDIATE: $(OBJ)

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(TARGET_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean