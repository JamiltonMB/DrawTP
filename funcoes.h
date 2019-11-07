#ifndef FUNCOES_H
#define FUNCOES_H

int dimx=0,dimy=0;

pixel** abrir_arquivo(char w[50]){ //função para letitura do arquivo
	FILE *img = fopen(w, "r");
    fscanf(img, "P3\n%d %d\n255\n", &dimx, &dimy);
    pixel **p;
    
	for(int i=0;i<dimx;i++)
    {
		for(int j=0;j<dimy;j++)
        {
            if(j!=dimy-1)
            {
    			fscanf(img,"%hd %hd %hd ",&p[i][j].red,&p[i][j].green,&p[i][j].blue);
            }
            else
            {
                fscanf(img,"%hd %hd %hd",&p[i][j].red,&p[i][j].green,&p[i][j].blue);
            }
		}
        char t;
        fscanf(img,"%c", &t);
	}
    fclose(img);
    return p;
}


pixel** image (int x,int y){ //Cria uma nova "imagem", com largura e altura especificadas
    FILE *fp = fopen("n.ppm", "w");
    pixel **p;
    dimx=x;
    dimy=y;
    if(fp == NULL)
    {
		printf("Erro na abertura do arquivo");
	}
    else
    {
        fprintf(fp, "P3\n%d %d\n255\n", x, y);
	for(int j=0;j<y;j++)
	{
		for(int i=0;i<x;i++)
		{   
            p[i][j].red=255;
		    p[i][j].green=255;
		    p[i][j].blue=255;
            if(j!=dimx-1)
            {
                fprintf(fp,"%d %d %d ",p[i][j].red,p[i][j].green,p[i][j].blue);
            }
	        else
            {
                fprintf(fp,"%d %d %d",p[i][j].red,p[i][j].green,p[i][j].blue);
            }
		}
		fprintf(fp,"\n");
	}
        fclose(fp);
    }
    return p;
}
void save(pixel **p){
    FILE *fp = fopen("n.ppm", "w");
    if(fp == NULL)
    {
	printf("Erro na abertura do arquivo");
    }
    else
    {
        fprintf(fp, "P3\n%d %d\n255\n", dimx, dimy);
	for(int j=0;j<dimy;j++)
	{
		for(int i=0;i<dimx;i++)
		{
            	    if(j!=dimx-1)
            	    {            
			fprintf(fp,"%d %d %d ",p[i][j].red,p[i][j].green,p[i][j].blue);
            	    }
	        else
            {
                    fprintf(fp,"%d %d %d",p[i][j].red,p[i][j].green,p[i][j].blue);
            }
	}
		fprintf(fp,"\n");
    }
        fclose(fp);
    }
}


/*void clear(pixel **p,unsigned short r, unsigned short g,unsigned short b){ //Limpa a imagem setando todos os pixels para uma cor especificada
    for(int j=0;j<dimy;j++)
	{
		for(int i=0;i<dimx;i++)
		{
            color(p[i][j],r,g,b);	
		}
    }
}


void AllocMatrix(int N, int M, Area** a) {
  int i;
  a = malloc(N * sizeof(Area *));
  for (i = 0; i < N; i++) {
    a[i] = calloc(M, sizeof(Area*));
  }
}


void rect(pixel **p){ //FUNÇÃO PARA DESENHAR RETÂNGULOS 
    for(i=___; i___; i++)
    {
        for(j=____; j___; j++)
        {
            color(p[i][j],255,255,255);
        }
    }
}*/

#endif






























#endif
