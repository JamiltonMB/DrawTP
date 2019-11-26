#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "structs.h"
#include "funcoes.h"

GtkWidget *window, *image, *button, *grid, *frame, *box, *txt_view, *scrolled_window, *entry, *label;
const gchar *entry_text;
gchar *v_texto;

GtkTextBuffer *buffer;
GtkTextIter start, end;
GtkTextIter iter;

char nome_espec[50];
char nome_image[50]="imagem.ppm";
pixel **p;

void get_espec(int t, char n[50], char str[t * 50])
{

    int i = 0;
    char linha[50];
    FILE *arq = fopen(n, "r");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo");
    }
    else
    {
        for (i = 0; i < t; i++)
        {
            fgets(linha, 50, arq);
            strcat(str, linha);
        }
        fclose(arq);
    }
}

static void button_salvar(gpointer data)
{
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    v_texto = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    strcpy(nome_espec, entry_text);
    FILE *arq = fopen(nome_espec, "w");
    if (arq == NULL)
    {
        printf("Erro no salvamento do arquivo\n");
    }
    else
    {
        strcat(v_texto, "\n");
        fputs(v_texto, arq);
        fclose(arq);
    }
    g_free(v_texto);
    ler_spc(p, nome_espec);
}

static void button_clicked(gpointer data)
{
    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    strcpy(nome_espec, entry_text);
    int tl = contar_spec(nome_espec);
    char str[tl * 50];
    char aux_str[0];
    strcpy(str, aux_str);
    get_espec(tl, nome_espec, str);
    gtk_text_buffer_set_text(buffer, str, -1);
}

static void button_atualizar(gpointer data)
{
    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    strcpy(nome_espec, entry_text);
    ler_save(nome_espec, nome_image);
    gtk_image_set_from_file(GTK_IMAGE(image), nome_image);//perguntar a jamilton
}

static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
    free(p);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    gtk_window_set_title(GTK_WINDOW(window), "DrawTP");

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);

    image = gtk_image_new_from_file(nome_image);
    button = gtk_button_new_with_label("Ler");
    grid = gtk_grid_new();
    entry = gtk_entry_new();
    label = gtk_label_new("   ARQUIVO DE \nESPECIFICAÇÃO: ");
    gtk_entry_set_max_length(GTK_ENTRY(entry), 49);

    gtk_entry_set_text(GTK_ENTRY(entry), nome_espec);

    buffer = gtk_text_buffer_new(NULL);

    txt_view = gtk_text_view_new_with_buffer(buffer);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(txt_view), GTK_WRAP_WORD);
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled_window), 500);
    gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled_window), 400);
    gtk_container_add(GTK_CONTAINER(scrolled_window), txt_view);
    gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 5);

    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);

    gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 2, 1, 1);
    button = gtk_button_new_with_label("SALVAR");
    g_signal_connect(button, "clicked", G_CALLBACK(button_salvar), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 3, 1);
    button = gtk_button_new_with_label("ATUALIZAR IMAGEM");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 3, 3, 1);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled_window), 600);
    gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled_window), 400);
    gtk_container_add(GTK_CONTAINER(scrolled_window), image);
    gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 5);

    frame = gtk_frame_new("Imagem: ");
    gtk_container_add(GTK_CONTAINER(frame), scrolled_window);

    box = gtk_box_new(0, 1);
    gtk_box_set_spacing(GTK_BOX(box), 10);
    gtk_box_pack_start(GTK_BOX(box), frame, 1, 1, 1);

    frame = gtk_frame_new("Configurações: ");
    gtk_frame_set_label_align(GTK_FRAME(frame), 0.5, 0.5);
    gtk_container_add(GTK_CONTAINER(frame), grid);

    gtk_box_pack_start(GTK_BOX(box), frame, 0, 0, 1);

    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(button, "clicked", G_CALLBACK(button_atualizar), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
