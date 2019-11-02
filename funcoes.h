#ifndef FUNCOES_H
#define FUNCOES_H

int dimx=0,dimy=0;

void abrir_arquivo(pixel **p,char w[50]){ //função para letitura do arquivo
	FILE *img = fopen(w, "r");
    fscanf(img, "P3\n%d %d\n255\n", &dimx, &dimy);

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
}

void image (int x,int y){ //Cria uma nova "imagem", com largura e altura especificadas
    FILE *fp = fopen("n.ppm", "w");
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
            if(j!=dimx-1)
            {            
		            fprintf(fp,"255 255 255 ");;
            }
	        else
            {
                    fprintf(fp,"255 255 255");;
            }
		}
		fprintf(fp,"\n");
	}
        fclose(fp);
    }
}

void color(pixel p,unsigned short r, unsigned short g,unsigned short b){
    p.red=r;
    p.green=g;
    p.blue=b;
}

/*void clear(pixel **p,unsigned short r, unsigned short g,unsigned short b){ //Limpa a imagem setando todos os pixels para uma cor especificada
    for(int j=0;j<dimy;j++)
	{
		for(int i=0;i<dimx;i++)
		{
            color(p[i][j],r,g,b);	
		}
}

void line(pixel **p,reta r){
    for(int j=0;j<dimy;j++)
	{
		for(int i=0;i<dimx;i++)
		{
            color(p[i][j],r,g,b);	
		}
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
