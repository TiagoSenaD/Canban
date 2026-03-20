#ifndef WINDOW_H
#define WINDOW_H

typedef struct {
    int largura;
    int altura;
    const char *titulo;
    const char *url_inicial;
} AppConfig;

void iniciar_interface(AppConfig config);

void atualizar_ui(const char *js_code);

#endif