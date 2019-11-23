#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

GtkWidget *window, *image, *button, *grid, *frame, *box, *txt_view, *scrolled_window, *entry, *label;
const gchar *entry_text;
gchar *v_texto;

GtkTextBuffer *buffer;
GtkTextIter start, end;
GtkTextIter iter;


char nome_espec[50]="espec.txt";
char nome_image[50];

int contar_spec(char n[50]){ //FUNÇÃO QUE CONTA A QUANTIDADE DE LINHAS DO ARQUIVO --- REPETIDA=========   
    int linhas=0;
    char c, f='\n';
    FILE *arq = fopen(n, "r");
	    if(arq == NULL)
		    {
		    printf("Erro na abertura do arquivo");
		    }
	    else
		    {            
                while(fread (&c, sizeof(char), 1, arq)) 
                {
                if(c == f) 
                    {
                        linhas++;
                    }
                } 
            fclose(arq);
		    }
return linhas;
}

void ler_spc(char n[50], char i_nome[50]){ //FUNÇÃO REPETIDA, RETIRAR DEPOIS DA JUNÇÃO DOS ARQUIVOS

	int i=0, j=0;
    char linha[50];
    char l_aux[50];
    char comparador[4];
    char save_img[50];
    FILE *arq = fopen(n, "r");
	if(arq == NULL)
		{
		printf("Erro na abertura do arquivo");
		}   
	else
		{
                for(i=0; i<(contar_spec(n)); i++)
                {
                fgets(linha, 50, arq);
                strcpy(l_aux, linha);
                memcpy(comparador, &linha[0], 4);
                comparador[4] = '\0';
                if(strcmp(comparador, "save")==0)//{fputs(l_aux, aux);}
                    {
                        for(j=0; j<(strlen(l_aux)-6); j++)
                        {
                        save_img[j]=linha[(j+5)];
                        save_img[j+1]='\0';                    
                        }
                        strcpy(i_nome, save_img);
                    }
                }       
        }
}

void vet_espec(int t, char vet_spc[t][50], char n[50], char str[t*50]){

    int i=0, y=0, j=0;
    char linha[50];
    FILE *arq = fopen(n, "r");
	if(arq == NULL)
		{
		printf("Erro na abertura do arquivo");
		}   
	else
		{
        for(i=0; i<t; i++)
            {
            fgets(linha, 50, arq);
            strcpy(vet_spc[i], linha);
            }
        for(i=0; i<t; i++)
            {
            strcat(str, vet_spc[i]);

            }
        }
}


static void button_clicked(gpointer data)
{

entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
//g_print("Entry contents: %s\n", entry_text);
strcpy(nome_espec, entry_text);
//printf("%s\n", nome_espec);
char teste[50];// por algum motivo o código só roda se essa variável exisitir, foi possuído pelo capeta, só pode!
int tl=contar_spec(nome_espec);
char vet_spc[tl][50];
char str[tl*50];
char *texto;

vet_espec(tl, vet_spc, nome_espec, str);
gtk_text_buffer_set_text(buffer, str, -1);

gtk_text_buffer_get_bounds (buffer, &start, &end);
v_texto = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
//g_print ("%s", v_texto);
g_free (v_texto);

}


static void destroy( GtkWidget *widget, gpointer data)
{
    gtk_main_quit ();
}


int main(int argc, char *argv[]) {

ler_spc(nome_espec, nome_image); //QUANDO JUNTAR OS ARQUIVOS ESSA FUNÇÃO DEVE SER MUDADA
    

  
gtk_init(&argc, &argv);

window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
gtk_container_set_border_width (GTK_CONTAINER (window), 20);
gtk_window_set_title(GTK_WINDOW(window), "DrawTP");

g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (destroy), NULL);

image = gtk_image_new_from_file(nome_image);
button = gtk_button_new_with_label("Ler");
grid = gtk_grid_new();
entry = gtk_entry_new ();
label = gtk_label_new ("   ARQUIVO DE \nESPECIFICAÇÃO: ");
gtk_entry_set_max_length (GTK_ENTRY(entry), 49);

gtk_entry_set_text (GTK_ENTRY(entry), nome_espec);

buffer = gtk_text_buffer_new (NULL);
//buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt_view));
txt_view = gtk_text_view_new_with_buffer (buffer);
gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (txt_view), GTK_WRAP_WORD);
scrolled_window = gtk_scrolled_window_new (NULL, NULL);
gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW (scrolled_window), 500);
gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW (scrolled_window), 400);
gtk_container_add (GTK_CONTAINER (scrolled_window), txt_view);
gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 5);

//gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
g_signal_connect(button,"clicked", G_CALLBACK(button_clicked), NULL);

gtk_grid_attach (GTK_GRID (grid), scrolled_window, 0, 0, 3, 1);
gtk_grid_attach (GTK_GRID (grid), label, 0, 2, 1, 1);
gtk_grid_attach (GTK_GRID (grid), entry, 1, 2, 1, 1);
gtk_grid_attach (GTK_GRID (grid), button, 2, 2, 1, 1);
button = gtk_button_new_with_label("SALVAR");
gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 3, 1);

scrolled_window = gtk_scrolled_window_new (NULL, NULL);
gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW (scrolled_window), 600);
gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW (scrolled_window), 400);
gtk_container_add (GTK_CONTAINER (scrolled_window), image);
gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 5);

frame = gtk_frame_new ("Imagem: ");
gtk_container_add (GTK_CONTAINER (frame), scrolled_window);

box = gtk_box_new(0, 1);
gtk_box_set_spacing (GTK_BOX(box), 10);
//gtk_box_pack_start(GTK_BOX(box), scrolled_window, 1, 1, 1);
gtk_box_pack_start(GTK_BOX(box), frame, 1, 1, 1);

frame = gtk_frame_new ("Configurações: ");
gtk_frame_set_label_align (GTK_FRAME (frame), 0.5, 0.5);
gtk_container_add (GTK_CONTAINER (frame), grid);

gtk_box_pack_start(GTK_BOX(box), frame, 0, 0, 1);

gtk_container_add(GTK_CONTAINER(window), box);

gtk_widget_show_all(window);
gtk_main();

return 0;
}
