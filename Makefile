CC = clang
CFLAGS = -Wall -Wextra -I./src/modulos/kanban/include
LDFLAGS = -L./build -lkanban -Wl,-rpath,'$$ORIGIN/build'

TARGET_DIR = ./bin
TARGET = $(TARGET_DIR)/kanban_app
SRC = src/main.c
MOD_DIR = src/modulos/kanban

all: $(TARGET)

build_module:
	$(MAKE) -C $(MOD_DIR)


$(TARGET): $(SRC) build_module
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)
	@echo "Executável gerado em: $(TARGET)"

run: all
	./$(TARGET)

clean:
	rm -rf $(TARGET_DIR) build/
	$(MAKE) -C $(MOD_DIR) clean

.PHONY: all clean run build_module