#ifndef FUNCOES_H
#define FUNCOES_H
#include "structs.h"

int dimx=0,dimy=0;

pixel** allocar(int L, int C) {
  int i;
  pixel **p;
  p = malloc(L * sizeof(pixel *));
  for (i = 0; i < L; i++) {
    p[i] = calloc(C, sizeof(pixel*));
  }
  return p;
}

pixel color(pixel p,unsigned short r, unsigned short g,unsigned short b){
    p.red=r;
    p.green=g;
    p.blue=b;
    return p;
}

pixel** image (int x,int y){ //Cria uma nova "imagem", com largura e altura especificadas
    FILE *fp = fopen("n.ppm", "w");
    dimx=x;
    dimy=y;
    pixel **p=allocar(dimx,dimy);
    if(fp == NULL)
    {
		printf("Erro na abertura do arquivo");
	}
    else
    {
        fprintf(fp, "P3\n%d %d\n255\n", x, y);
	    for(int i=0;i<dimy;i++)
	    {
		    for(int j=0;j<dimx;j++)
		    {   
                p[i][j]=color(p[i][j],255,255,255);
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

pixel** abrir_arquivo(char w[50]){ //função para letitura do arquivo
	FILE *img = fopen(w, "r");
    fscanf(img, "P3\n%d %d\n255\n", &dimx, &dimy);
    pixel **p;
    p=allocar(dimx,dimy);
    
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


void linha(pixel **p,reta r){ //https://gist.github.com/mfilipelino/11240714#file-paintopengl-c
    int dy = (r.p2.y - r.p1.y); //Diferença entre os pontos y2 e y1
    int dx = (r.p2.x - r.p1.x); //Diferença entre os pontos x2 e x1
    int sx,sy; //Variaveis que serão utilizadas para armazenar o sinal de x e y afim de saber o quadrante do segmento
    int i=r.p1.y;
    int j=r.p1.x;
    if(r.p1.x<r.p2.x) //Determinar os sinais de x e y
    {
        sx=1;
    }
    else
    {
        sx=-1;
    }

    if(r.p1.y<r.p2.y)
    {
        sy=1;
    }
    else
    {
        sy=-1;
    }                  //fim da determinação de sinais
    
    int erro;
    int erroTemp;
    if(dx>dy) // Definição do erro inicial baseado na maior diferença
    {
        erro=dx/2;
    }
    else
    {
        erro=(-dy)/2;
    }
    
    while(true)
	{
	    p[i][j]=color(p[i][j],0,0,0);
        if((i==r.p2.y)&&(j==r.p2.x)) // Testa se chegou ao ponto final e encerra o algoritimo
        {
            break;
        }

        erroTemp=erro;

        if(erroTemp > -dx)
        {
            erro -= dy;
            j += sx;
        }
        
        if(erroTemp < dy)
        {
            erro += dx;
            i += sy;
        }
	}
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
        for(int i=0;i<dimx;i++)
		{
			for(int j=0;j<dimy;j++)
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

void polygon(pixel **p,int l, int x[l],int y[l]){
    reta r;
    for(int i=1;i<=l;i++)
    {
        r.p1.x=x[i-1];
        r.p1.y=y[i-1];
        r.p2.x=x[i];
        r.p2.y=y[i];
        linha(p,r);
    }
}

void clear(pixel **p,unsigned short r, unsigned short g,unsigned short b){ //Limpa a imagem setando todos os pixels para uma cor especificada
    for(int j=0;j<dimy;j++)
	{
		for(int i=0;i<dimx;i++)
		{
            p[i][j]=color(p[i][j],r,g,b);	
		}
    }
}

#endif
