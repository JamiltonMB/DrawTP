#include <stdio.h>
#include <string.h>

typedef struct formas_s_q{   //Struc criada para armazenar os dados das formas geométricas

int posx, posy, tamx, tamy;

}formas_q;

void abrir_arquivo(int L, int C, int vet[L][C][3]){ //função para letitura do arquivo
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

void rect(int C, int L, int vet[L][C][3], formas_q q){ //função para desenhar retângulos
    int R=10, B=10, G=10, i, j;
    for(i=q.posy; i<(q.posy+q.tamy); i++)
        {
        for(j=q.posx; j<(q.posx+q.tamx); j++)
            {
            vet[i][j][0]=R;
            vet[i][j][1]=B;
            vet[i][j][2]=G;
            }
        }
}

formas_q fundo_f(formas_q fundo){ //função com strct para armazenar os dados do plano de fundo da imagem
    fundo.posx=10, fundo.posy=0;
    printf("Insira o tamanho da imagem em pixels, Colunas(Largura) x Linhas(Altura):\n");
    scanf("%d %d", &fundo.tamx, &fundo.tamy);
    return fundo;
}

void gerar_img(int L, int C, int vet[L][C][3], formas_q fundo){ //função para gerar imagens
int R=250, B=250, G=250, i, j;
for(i=0; i<fundo.tamy; i++)
    {
    for(j=0; j<fundo.tamx; j++)
        {
        vet[i][j][0]=R;
        vet[i][j][1]=B;
        vet[i][j][2]=G;
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


int main(){

formas_q fundo;
fundo = fundo_f(fundo);
int vet[fundo.tamx][fundo.tamy][3];

formas_q q;
q.posx=10, q.posy=10, q.tamx=20, q.tamy=20;

int i, j;

gerar_img(fundo.tamx, fundo.tamy, vet, fundo);

//rect(C, L, vet, q); // teste da função geradora de retângulos

int RBG=3;
abrir_arquivo(fundo.tamy, fundo.tamx, vet);

for(i=0; i<fundo.tamy; i++){
    for(j=0; j<fundo.tamx; j++){
        for(int k=0; k<3; k++){
        printf("%d\n", vet[i][j][j]);
        }
    }
}

return 0;
}
