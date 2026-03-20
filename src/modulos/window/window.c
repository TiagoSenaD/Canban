#include "window.h"
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static WebKitWebView *global_web_view;

void iniciar_interface(AppConfig config) {
    int argc = 0;
    char **argv = NULL;
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), config.largura, config.altura);
    gtk_window_set_title(GTK_WINDOW(window), config.titulo);

    global_web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(global_web_view));

    webkit_web_view_load_uri(global_web_view, config.url_inicial);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}

void atualizar_ui(const char *js_code) {
    if (global_web_view) {
        webkit_web_view_evaluate_javascript(global_web_view, js_code, -1, NULL, NULL, NULL, NULL, NULL);
    }
}