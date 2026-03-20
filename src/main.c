#include "modulos/window/include/window.h"

int main() {
    AppConfig config = {
        .largura = 1024,
        .altura = 768,
        .titulo = "C-Tauri Kanban",
        .url_inicial = "https://www.google.com"
    };

    iniciar_interface(config);
    return 0;
}