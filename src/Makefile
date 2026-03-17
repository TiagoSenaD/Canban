CC = clang
CFLAGS = -Wall -Wextra -I./modulos/kanban/include
LDFLAGS = -L../build -lkanban -Wl,-rpath,'$$ORIGIN/../build'

TARGET_DIR = ../bin
TARGET = $(TARGET_DIR)/kanban_app
SRC = main.c


all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@
	@echo "Executável gerado em: $(TARGET)"

run: all
	LD_LIBRARY_PATH=../build $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean run