#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct espec_s{   //STRUCT PARA ARMAZENAR O ARQUIVO DE ESPECIFICAÇÃO
int image[2], clear[3], color[3], line[4], polygon[7], circle[3], color2[3], fill[2], color3[3], fill2[2];
}espec;

typedef struct formas_s_q{   //STRUCT PARA ARMAZENAR DADOS DE QUADRADOS E RETÂNGULOS
int posx, posy, tamx, tamy;
}formas_q;

void abrir_arquivo(int L, int C, int vet[L][C][3]){ //FUNÇÃO PARA ABERTURAS DE IMAGENS (CHECKPOINT 2) -- FALTA MELHORIAS
	FILE *img = fopen("imagem.ppm", "r");
	for(int i=0;i<L;i++){
		for(int j=0;j<C;j++){
			for(int k=0;k<3;k++){
				fscanf(img,"%d ",&vet[i][j][k]);
			}
		}
	}
    fclose(img);
}

void rect(int C, int L, int vet[L][C][3], formas_q q){ //FUNÇÃO PARA DESENHAR RETÂNGULOS (CHECKPOINT 2) -- FALTA MELHORIAS
    int R=10, G=10, B=10, i, j; //Para fins de teste os valores referentes as cores foram fixados
    for(i=q.posy; i<(q.posy+q.tamy); i++)
        {
        for(j=q.posx; j<(q.posx+q.tamx); j++)
            {
            vet[i][j][0]=R;
            vet[i][j][1]=G;
            vet[i][j][2]=B;
            }
        }
}

formas_q fundo_f(formas_q fundo, int tx, int ty){ //FUNÇÃO DO TIPO STRUCT PARA ARMAZENAR DOS DADOS DO PLANO DE FUNDO DA IMAGEM
    //fundo.posx=10, fundo.posy=0;
    //printf("Insira o tamanho da imagem em pixels, Colunas(Largura) x Linhas(Altura):\n");
    //scanf("%d %d", &fundo.tamx, &fundo.tamy);
    fundo.tamx = tx;
    fundo.tamy = ty;
    return fundo;
}

void gerar_img(int L, int C, int ***vet, formas_q fundo){ //FUNÇÃO PARA GERAR IMAGEM (IMAGE)
	int R=250, G=250, B=250, i, j;
	for(i=0; i<fundo.tamy; i++)
		{
		for(j=0; j<fundo.tamx; j++)
		    {
		    vet[i][j][0]=R;
		    vet[i][j][1]=G;
		    vet[i][j][2]=B;
		    }
		}

	FILE *img = fopen("imagem.ppm", "w");
	if(img == NULL)
		{
		printf("Erro na abertura do arquivo");
		}
	else
		{
		fprintf(img, "P3\n%d %d\n255\n", fundo.tamx, fundo.tamy);
		for(i=0; i<fundo.tamy; i++)
		    {
		    for(j=0; j<fundo.tamx; j++)
		        {
		        if(j!=fundo.tamx-1)
		            {            
		            fprintf(img, "%d %d %d ", vet[i][j][0], vet[i][j][1], vet[i][j][2]);
		            }
		        else
		            {
		            fprintf(img, "%d %d %d", vet[i][j][0], vet[i][j][1], vet[i][j][2]);
		            }
		        }
		    fprintf(img, "\n");
		   // fprintf(img, "#Fim da %dª linha\n", i+1);  //Código usado para visualizar o tamanho das linhas     
		    }
		fclose(img);
		}
}

int save(int L, int C, int ***vet, formas_q fundo){ //FUNÇÃO PARA SALVAR IMAGENS (SAVE)
	int i, j;
	FILE *img = fopen("imagem.ppm", "w");
	if(img == NULL)
		{
		printf("Erro na abertura do arquivo");
		}
	else
		{
		fprintf(img, "P3\n%d %d\n255\n", fundo.tamx, fundo.tamy);
		for(i=0; i<fundo.tamy; i++)
		    {
		    for(j=0; j<fundo.tamx; j++)
		        {
		        if(j!=fundo.tamx-1)
		            {            
		            fprintf(img, "%d %d %d ", vet[i][j][0], vet[i][j][1], vet[i][j][2]);
		            }
		        else
		            {
		            fprintf(img, "%d %d %d", vet[i][j][0], vet[i][j][1], vet[i][j][2]);
		            }
		        }
		    fprintf(img, "\n");
		   // fprintf(img, "#Fim da %dª linha\n", i+1);  //Código usado para visualizar o tamanho das linhas     
		    }
		fclose(img);
		}
}

espec ler_espec(espec a){ //FUNÇÃO PARA LER O ARQUIVO DE ESPECIFICAÇÃO
	int i, j;
	FILE *arq = fopen("espec.txt", "r");
	if(arq == NULL)
		{
		printf("Erro na abertura do arquivo");
		}
	else
		{
        fscanf(arq, "image %d %d\n", &a.image[0], &a.image[1]);
        fscanf(arq, "clear %d %d %d\n", &a.clear[0], &a.clear[1], &a.clear[2]);
        fscanf(arq, "color %d %d %d\n", &a.color[0], &a.color[1], &a.color[2]);
        fscanf(arq, "line %d %d %d %d\n", &a.line[0], &a.line[1], &a.line[2], &a.line[3]);
        fscanf(arq, "polygon %d %d %d %d %d %d %d\n", &a.polygon[0], &a.polygon[1], &a.polygon[2], &a.polygon[3], &a.polygon[4], &a.polygon[5], &a.polygon[6]);
        fscanf(arq, "circle %d %d %d\n", &a.circle[0], &a.circle[1], &a.circle[2]);
        fscanf(arq, "color %d %d %d\n", &a.color2[0], &a.color2[1], &a.color2[2]);
        fscanf(arq, "fill %d %d\n", &a.fill[0], &a.fill[1]);
        fscanf(arq, "color %d %d %d\n", &a.color3[0], &a.color3[1], &a.color3[2]);
        fscanf(arq, "fill %d %d\n", &a.fill2[0], &a.fill2[1]);		
		fclose(arq);
		}
return a;
}

int *** aloc_f(int t1, int t2, int t3){ //FUNÇÃO COM ALOCAÇÃO DINÂMICA DE MEMÓRIA
    int i, j;
    int ***vet = malloc(sizeof(int**)*t1);
    for(i=0;i<t1; i++)
	    {
	    vet[i] = malloc(sizeof(int*)*t2);
	    }
    for(i=0;i<t1;i++)
	    {
	    for(j=0;j<t2;j++)
	        {
		    vet[i][j]=malloc(sizeof(int)*t3);
	        }
        }
    return vet;
}

int main(){

espec arquivo;
arquivo = ler_espec(arquivo);

formas_q fundo;
fundo = fundo_f(fundo, arquivo.image[0], arquivo.image[1]);

int ***vet=NULL;
vet = aloc_f(fundo.tamy, fundo.tamx, 3);

gerar_img(fundo.tamx, fundo.tamy, vet, fundo);

return 0;
}
