#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int xtz=3;
typedef struct espec_s{   //STRUCT PARA ARMAZENAR O ARQUIVO DE ESPECIFICAÇÃO
int image[2], clear[3], color[50][3], line[50][4], polygon[50][7], circle[50][3], fill[50][2],rect[50][4];
char save[50];
}espec;

typedef struct t_tipos_s{
int color_t, line_t, polygon_t, circle_t, fill_t, rect_t;
}t_tipos;

int contar_spec(char n[50]){ //FUNÇÃO QUE CONTA A QUANTIDADE DE LINHAS DO ARQUIVO    
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
//printf("%d\n", linhas);
return linhas;
}

t_tipos tam_tip(char n[50]){//FUNÇÃO QUE CONTA A QUANTIDADE DE TIPOS DO ARQUIVO DE ESPECIFICAÇÃO
    t_tipos a;
    a.color_t=0; a.line_t=0; a.polygon_t=0; a.circle_t=0; a.fill_t=0; a.rect_t=0;
	int i=0, j=0, t=0;
    char linha[50];
    char l_aux[50];
    char comparador[4];
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
            if(strcmp(comparador, "colo")==0){a.color_t++;}
            else if(strcmp(comparador, "line")==0){a.line_t++;}
            else if(strcmp(comparador, "poly")==0){a.polygon_t++;}
            else if(strcmp(comparador, "circ")==0){a.circle_t++;}
            else if(strcmp(comparador, "fill")==0){a.fill_t++;}
            else if(strcmp(comparador, "rect")==0){a.rect_t++;}
            }
        fclose(arq);             
	    }
    return a;
}

espec ler_espec(char n[50], char tipo[10]){ //FUNÇÃO PARA LER O ARQUIVO DE ESPECIFICAÇÃO
    espec a;
    t_tipos tam=tam_tip(n);
	int i=0, j=0, t=0;
    char linha[50];
    char l_aux[50];
    char comparador[4];
    char save_aux[50];
	FILE *arq = fopen(n, "r");
    FILE *aux = fopen("aux.txt", "w");
	if(aux == NULL)
		{
		printf("Erro na abertura do arquivo");
		} 
	if(arq == NULL)
		{
		printf("Erro na abertura do arquivo");
		}   
	else
		{
        if(strcmp(tipo, "color")==0)
            {
                for(i=0; i<(contar_spec(n)); i++)
                {
                fgets(linha, 50, arq);
                strcpy(l_aux, linha);
                memcpy(comparador, &linha[0], 4);
                comparador[4] = '\0';
                if(strcmp(comparador, "colo")==0){fputs(l_aux, aux);}
                }
                fclose(aux);
                FILE *aux = fopen("aux.txt", "r");           
                for(i=0; i<tam.color_t; i++)
                {
                fscanf(aux, "color %d %d %d\n", &a.color[i][0], &a.color[i][1], &a.color[i][2]);
                }
            }
        else if(strcmp(tipo, "line")==0)
            {
                for(i=0; i<(contar_spec(n)); i++)
                {
                fgets(linha, 50, arq);
                strcpy(l_aux, linha);
                memcpy(comparador, &linha[0], 4);
                comparador[4] = '\0';
                if(strcmp(comparador, "line")==0){fputs(l_aux, aux);}
                }
                fclose(aux);
                FILE *aux = fopen("aux.txt", "r");            
                for(i=0; i<tam.line_t; i++)
                {
                fscanf(aux, "line %d %d %d %d\n", &a.line[i][0], &a.line[i][1], &a.line[i][2], &a.line[i][3]);
                }
            }
        else if(strcmp(tipo, "polygon")==0)
            {
                for(i=0; i<(contar_spec(n)); i++)
                {
                fgets(linha, 50, arq);
                strcpy(l_aux, linha);
                memcpy(comparador, &linha[0], 4);
                comparador[4] = '\0';
                if(strcmp(comparador, "poly")==0){fputs(l_aux, aux);}
                }
                fclose(aux);
                FILE *aux = fopen("aux.txt", "r");            
                for(i=0; i<tam.polygon_t; i++)
                {
                fscanf(aux, "polygon %d %d %d %d %d %d %d\n", &a.polygon[i][0], &a.polygon[i][1], &a.polygon[i][2], &a.polygon[i][3], &a.polygon[i][4], &a.polygon[i][5], &a.polygon[i][6]);
                }
            }
        else if(strcmp(tipo, "circle")==0)
            {
                for(i=0; i<(contar_spec(n)); i++)
                {
                fgets(linha, 50, arq);
                strcpy(l_aux, linha);
                memcpy(comparador, &linha[0], 4);
                comparador[4] = '\0';
                if(strcmp(comparador, "circ")==0){fputs(l_aux, aux);}
                }
                fclose(aux);
                FILE *aux = fopen("aux.txt", "r");           
                for(i=0; i<tam.circle_t; i++)
                {
                fscanf(aux, "circle %d %d %d\n", &a.circle[i][0], &a.circle[i][1], &a.circle[i][2]);
                }
            }     
        else if(strcmp(tipo, "fill")==0)
            {
                for(i=0; i<(contar_spec(n)); i++)
                {
                fgets(linha, 50, arq);
                strcpy(l_aux, linha);
                memcpy(comparador, &linha[0], 4);
                comparador[4] = '\0';
                if(strcmp(comparador, "fill")==0){fputs(l_aux, aux);}
                }
                fclose(aux);
                FILE *aux = fopen("aux.txt", "r");           
                for(i=0; i<tam.fill_t; i++)
                {
                fscanf(aux, "fill %d %d\n", &a.fill[i][0], &a.fill[i][1]);
                }
            }
        else if(strcmp(tipo, "rect")==0)
            {
                for(i=0; i<(contar_spec(n)); i++)
                {
                fgets(linha, 50, arq);
                strcpy(l_aux, linha);
                memcpy(comparador, &linha[0], 4);
                comparador[4] = '\0';
                if(strcmp(comparador, "rect")==0){fputs(l_aux, aux);}
                }
                fclose(aux);
                FILE *aux = fopen("aux.txt", "r");            
                for(i=0; i<tam.rect_t; i++)
                {
                fscanf(aux, "rect %d %d %d %d\n", &a.rect[i][0], &a.rect[i][1], &a.rect[i][2], &a.rect[i][3]);
                }
            }
        else if(strcmp(tipo, "image")==0)
            {
                for(i=0; i<(contar_spec(n)); i++)
                {
                fgets(linha, 50, arq);
                strcpy(l_aux, linha);
                memcpy(comparador, &linha[0], 4);
                comparador[4] = '\0';
                if(strcmp(comparador, "imag")==0){fputs(l_aux, aux);}
                }
                fclose(aux);
                FILE *aux = fopen("aux.txt", "r"); 
                fscanf(aux, "image %d %d\n", &a.image[0], &a.image[1]);  
            }
        else if(strcmp(tipo, "clear")==0)
            {
                for(i=0; i<(contar_spec(n)); i++)
                {
                fgets(linha, 50, arq);
                strcpy(l_aux, linha);
                memcpy(comparador, &linha[0], 4);
                comparador[4] = '\0';
                if(strcmp(comparador, "clea")==0){fputs(l_aux, aux);}
                }
                fclose(aux);
                FILE *aux = fopen("aux.txt", "r");                                 
                fscanf(aux, "clear %d %d %d\n", &a.clear[0], &a.clear[1], &a.clear[2]);
            }
        else if(strcmp(tipo, "save")==0)
            {
                for(i=0; i<(contar_spec(n)); i++)
                {
                fgets(linha, 50, arq);
                strcpy(l_aux, linha);
                memcpy(comparador, &linha[0], 4);
                comparador[4] = '\0';
                if(strcmp(comparador, "save")==0){fputs(l_aux, aux);}
                }
                fclose(aux);
                FILE *aux = fopen("aux.txt", "r");
                fgets(linha, 50, aux);           
                for(i=0; i<(strlen(linha)-6); i++){
                save_aux[i]=linha[(i+5)];                    
                }
                save_aux[(strlen(linha))]='\0';
                strcpy(a.save, save_aux);      
            }
        }
        fclose(aux);
        fclose(arq);
return a;        
}

espec ler_tudo(char n[50]){
espec a;
a = ler_espec(n, "color");
a = ler_espec(n, "line");
a = ler_espec(n, "polygon");
a = ler_espec(n, "circle");
a = ler_espec(n, "fill");
a = ler_espec(n, "rect");
a = ler_espec(n, "image");
a = ler_espec(n, "clear");
a = ler_espec(n, "save");
return a;
}




int main(){

espec arquivo;
t_tipos t;
t = tam_tip("espec.txt");
arquivo = ler_tudo("espec.txt");

printf("color %d\n", t.color_t);
printf("line %d\n", t.line_t);
printf("polygon %d\n", t.polygon_t);
printf("circle %d\n", t.circle_t);
printf("fill %d\n", t.fill_t);
printf("rect %d\n", t.rect_t);

printf("polygon: ");
for(int i=0; i<7; i++){printf("%d ", arquivo.polygon[0][i]);}
printf("\n");
printf("color: ");
for(int i=0; i<3; i++){printf("%d ", arquivo.color[0][i]);}
printf("\n");
printf("line: ");
for(int i=0; i<4; i++){printf("%d ", arquivo.line[0][i]);}
printf("\n");
printf("save: %s\n", arquivo.save);
printf("clear: ");
for(int i=0; i<3; i++){printf("%d ", arquivo.clear[i]);}
printf("\n");
printf("image: %d %d", arquivo.image[0], arquivo.image[1]);
printf("\n");
printf("rect: ");
for(int i=0; i<4; i++){printf("%d ", arquivo.rect[0][i]);}
printf("\n");
return 0;
}
