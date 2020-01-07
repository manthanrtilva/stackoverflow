#include <glib/gi18n.h>
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkWidget *dialog;

    gtk_init(&argc, &argv);

    dialog = gtk_dialog_new_with_buttons(
    "Title", NULL, 0,
    GTK_STOCK_CANCEL,
    GTK_RESPONSE_CANCEL,
    GTK_STOCK_OK,
    GTK_RESPONSE_OK,
    NULL);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return 0;
}