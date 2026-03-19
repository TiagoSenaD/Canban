CC = clang
# Mantendo suas flags e caminhos de include
CFLAGS = -Wall -Wextra -fPIC -Isrc/modulos/kanban/include -Isrc/modulos/helpers/include
LDFLAGS_DEV = -Lbuild -Wl,-rpath,'./build'

BUILD_DIR = build
BIN_DIR = bin

# Definindo os caminhos exatos dos fontes dos módulos
HELPERS_SRC = src/modulos/helpers/helpers.c
KANBAN_SRC = src/modulos/kanban/kanban.c

# Alvos de saída
HELPERS_SO = $(BUILD_DIR)/libhelpers.so
KANBAN_SO = $(BUILD_DIR)/libkanban.so
TARGET_DEV = $(BIN_DIR)/kanban_app_dev
TARGET_REL = $(BIN_DIR)/kanban_app_release

# --- MODO DEV (Padrão) ---
all: $(BUILD_DIR) $(BIN_DIR) $(HELPERS_SO) $(KANBAN_SO) $(TARGET_DEV)

# --- MODO RELEASE ---
release: CFLAGS += -O3
release: $(BUILD_DIR) $(BIN_DIR) $(TARGET_REL)
	strip $(TARGET_REL)
	@echo "✔ Release gerada: $(TARGET_REL)"

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regras específicas para as bibliotecas compartilhadas (DEV)
$(HELPERS_SO): $(HELPERS_SRC)
	$(CC) $(CFLAGS) -shared $< -o $@

$(KANBAN_SO): $(KANBAN_SRC)
	$(CC) $(CFLAGS) -shared $< -o $@

# Executável de Desenvolvimento (Dynamic Linking)
$(TARGET_DEV): src/main.c $(HELPERS_SO) $(KANBAN_SO)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS_DEV) -lhelpers -lkanban

# Executável de Release (Static Linking - Compila tudo junto)
$(TARGET_REL): src/main.c $(HELPERS_SRC) $(KANBAN_SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all release clean