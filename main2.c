#include <stdio.h>
#include <string.h>

typedef struct formas_s_q{   //Struc criada para 

int posx, posy, tamx, tamy;

}formas_q;

void abrir_arquivo(int L,int C,int vet[L][C][3]){
	FILE *img = fopen("imagem.ppm", "r");
	for(int i=0;i<L;i++){
		for(int j=0;j<C;j++){
			for(int k=0;k<3;k++){
				fscanf(img,"%d ",&vet[i][j][k]);
			}
		}
	}
}

void rect(int C, int L, int vet[L][C][3], formas_q q){
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


int main(){

formas_q q;
q.posx=10, q.posy=10, q.tamx=20, q.tamy=20;

int R=255, B=255, G=255, C, L, i, j;
printf("Insira o tamanho da imagem em pixels, Colunas x Linhas:\n");
scanf("%d %d", &C, &L);

int vet[L][C][3];

for(i=0; i<L; i++)
    {
    for(j=0; j<C; j++)
        {
        vet[i][j][0]=R;
        vet[i][j][1]=B;
        vet[i][j][2]=G;
        }
    }

//rect(C, L, vet, q);

FILE *img = fopen("imagem.ppm", "w");

if(img == NULL)
    {
    printf("Erro na abertura do arquivo");
    }
else
    {
    fprintf(img, "P3\n%d %d\n255\n", C, L);
    for(i=0; i<L; i++)
        {
        for(j=0; j<C; j++)
            {
            if(j!=C-1)
                {            
                fprintf(img, "%d %d %d ", vet[i][j][0], vet[i][j][1], vet[i][j][2]);
                }
            else
                {
                fprintf(img, "%d %d %d", vet[i][j][0], vet[i][j][1], vet[i][j][2]);
                }
            }
        fprintf(img, "\n");
        fprintf(img, "#Fim da %dª linha\n", i+1);       
        }
    fclose(img);
    }


return 0;
}
