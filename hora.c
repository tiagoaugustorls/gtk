#include <gtk/gtk.h>
#include <time.h>

void update_time(GtkLabel *label) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    char buffer[256];
    strftime(buffer, sizeof(buffer), "Data: %d/%m/%Y\nHora: %H:%M:%S", local);

    gtk_label_set_text(label, buffer);
}

static gboolean refresh_time(gpointer data) {
    update_time(GTK_LABEL(data));
    return TRUE; // Retorna TRUE para continuar chamando
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *label;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hora e Data do Sistema");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    label = gtk_label_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), label);

    update_time(GTK_LABEL(label));
    g_timeout_add_seconds(1, refresh_time, label); // Atualiza a cada 1 segundo

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
