#ifndef FUNCOES_H
#define FUNCOES_H
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

int dimx,dimy;

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
    int dy = abs(r.p2.y - r.p1.y); //Diferença entre os pontos y2 e y1
    int dx = abs(r.p2.x - r.p1.x); //Diferença entre os pontos x2 e x1
    int sx,sy; //Variaveis que serão utilizadas para armazenar o sinal de x e y
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
        if((i==r.p2.y)&&(j==r.p2.x)) // Testa se chegou ao ponto final da reta
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
    for(int i=1;i<l;i++)
    {
        r.p1.x=x[i-1];
        r.p1.y=y[i-1];
        r.p2.x=x[i];
        r.p2.y=y[i];
        linha(p,r);
    }
    r.p1.x=x[0];
    r.p1.y=y[0];
    linha(p,r);
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

void circulo(pixel **p,ponto c,int r){ // https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
    //Função criada com algoritimo de Bresenham, através dos conhecimentos do pdf disponibilizados pelo professor juntamente com o link adicionado acima
    int xc, yc;
    xc=c.x;
    yc=c.y;
    int x = 0;
    int y = r;

    int d = 1 - r;
    
    p[xc + x][yc + y]=color(p[xc + x][yc + y],0,0,0);
    p[xc - x][yc + y]=color(p[xc - x][yc + y],0,0,0);
    p[xc + x][yc - y]=color(p[xc + x][yc - y],0,0,0);
    p[xc - x][yc - y]=color(p[xc - x][yc - y],0,0,0);
    p[xc + y][yc + x]=color(p[xc + y][yc + x],0,0,0);
    p[xc - y][yc + x]=color(p[xc - y][yc + x],0,0,0);
    p[xc + y][yc - x]=color(p[xc + y][yc - x],0,0,0);
    p[xc - y][yc - x]=color(p[xc - y][yc - x],0,0,0);

    while(x <= y){
        x++;
        if(d < 0){
            d = d + 2*x + 1;
        }
        else{
            y--;
            d = d + 2*(x-y) + 1;
        }

    p[xc + x][yc + y]=color(p[xc + x][yc + y],0,0,0);
    p[xc - x][yc + y]=color(p[xc - x][yc + y],0,0,0);
    p[xc + x][yc - y]=color(p[xc + x][yc - y],0,0,0);
    p[xc - x][yc - y]=color(p[xc - x][yc - y],0,0,0);
    p[xc + y][yc + x]=color(p[xc + y][yc + x],0,0,0);
    p[xc - y][yc + x]=color(p[xc - y][yc + x],0,0,0);
    p[xc + y][yc - x]=color(p[xc + y][yc - x],0,0,0);
    p[xc - y][yc - x]=color(p[xc - y][yc - x],0,0,0);
    }
}

void fill(pixel **p,int x,int y,pixel cor){
    printf("x:%d :\n",x);
    printf("y:%d :\n",y);
    if(x<0 || x>=dimx || y<0 || y>=dimy)
    {
        return;
    }
    
    p[x][y]=color(p[x][y],cor.red,cor.green,cor.blue);
    
    fill(p,x+1,y,cor);
    fill(p,x,y+1,cor);
    fill(p,x-1,y,cor);
    fill(p,x,y-1,cor);        
}


void react(pixel **p, int x, int y, int A, int L){//FUNÇÃO PARA DESENHAR RETÂNGULOS
reta r;
for(int i=1; i<=4; i++)
	{
	if(i==1 || i==2)
		{
		r.p1.x=x;
		r.p1.y=y;
		r.p2.x=(x+L);
		r.p2.y=y;
		linha(p, r);
		if(i==1){y=y+A;}else{y=y-A;}
		}
	else{
		r.p1.x=x;
		r.p1.y=y;
		r.p2.x=x;
		r.p2.y=(y+A);
		linha(p, r);
		x=x+L;
		}
	}


}

#endif
