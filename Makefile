CC = clang
LDFLAGS_DEV = -Lbuild -Wl,-rpath,'./build' 
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0 webkit2gtk-4.1)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0 webkit2gtk-4.1)
CFLAGS = -Wall -Wextra -fPIC \
         -Isrc/modulos/kanban/include \
         -Isrc/modulos/helpers/include \
         -Isrc/modulos/window/include \
         $(GTK_CFLAGS)


BUILD_DIR = build
BIN_DIR = bin

HELPERS_SRC = src/modulos/helpers/helpers.c
KANBAN_SRC = src/modulos/kanban/kanban.c
WINDOW_SRC = src/modulos/window/window.c

HELPERS_SO = $(BUILD_DIR)/libhelpers.so
KANBAN_SO = $(BUILD_DIR)/libkanban.so
WINDOW_SO = $(BUILD_DIR)/libwindow.so

TARGET_DEV = $(BIN_DIR)/kanban_app_dev
TARGET_REL = $(BIN_DIR)/kanban_app_release

all: $(BUILD_DIR) $(BIN_DIR) $(HELPERS_SO) $(KANBAN_SO) $(WINDOW_SO) $(TARGET_DEV)

release: CFLAGS += -O3
release: $(BUILD_DIR) $(BIN_DIR) $(TARGET_REL)
	strip $(TARGET_REL)
	@echo "✔ Release gerada: $(TARGET_REL)"

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(HELPERS_SO): $(HELPERS_SRC)
	$(CC) $(CFLAGS) -shared $< -o $@

$(KANBAN_SO): $(KANBAN_SRC)
	$(CC) $(CFLAGS) -shared $< -o $@

$(WINDOW_SO): $(WINDOW_SRC)
	$(CC) $(CFLAGS) $(GTK_LIBS) -shared $< -o $@

$(TARGET_DEV): src/main.c $(HELPERS_SO) $(KANBAN_SO) $(WINDOW_SO)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS_DEV) -lhelpers -lkanban -lwindow $(GTK_LIBS)

$(TARGET_REL): src/main.c $(HELPERS_SRC) $(KANBAN_SRC) $(WINDOW_SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all release clean