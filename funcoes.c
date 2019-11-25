#ifndef FUNCOES_C
#define FUNCOES_C
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dimx;
int dimy;

pixel **allocar(int L, int C)
{
	int i;
	pixel **p;
	p = malloc(L * sizeof(pixel *));
	for (i = 0; i < L; i++)
	{
		p[i] = calloc(C, sizeof(pixel *));
	}
	return p;
}

pixel color(pixel p, unsigned short r, unsigned short g, unsigned short b)
{
	p.red = r;
	p.green = g;
	p.blue = b;
	return p;
}

pixel **imagem(char n[50], int x, int y)
{ //Cria uma nova "imagem", com largura e altura especificadas
	FILE *fp = fopen(n, "w");
	dimx = x;
	dimy = y;
	pixel **p = allocar(dimx, dimy);
	if (fp == NULL)
	{
		printf("Erro na abertura do arquivo");
	}
	else
	{
		fprintf(fp, "P3\n%d %d\n255\n", x, y);
		for (int j = 0; j < dimy; j++)
		{
			for (int i = 0; i < dimx; i++)
			{
				p[i][j] = color(p[i][j], 255, 255, 255);
				if (i != dimx - 1)
				{
					fprintf(fp, "%d %d %d ", p[i][j].red, p[i][j].green, p[i][j].blue);
				}
				else
				{
					fprintf(fp, "%d %d %d", p[i][j].red, p[i][j].green, p[i][j].blue);
				}
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
	return p;
}

pixel **abrir_arquivo(char w[50])
{ //função para letitura do arquivo
	FILE *img = fopen(w, "r");
	fscanf(img, "P3\n%d %d\n255\n", &dimx, &dimy);
	pixel **p;
	p = allocar(dimx, dimy);

	for (int j = 0; j < dimy; j++)
	{
		for (int i = 0; i < dimx; i++)
		{
			if (i != dimx - 1)
			{
				fscanf(img, "%hd %hd %hd ", &p[i][j].red, &p[i][j].green, &p[i][j].blue);
			}
			else
			{
				fscanf(img, "%hd %hd %hd", &p[i][j].red, &p[i][j].green, &p[i][j].blue);
			}
		}
		char t;
		fscanf(img, "%c", &t);
	}
	fclose(img);
	return p;
}

void linha(pixel **p, reta r)
{								   //https://gist.github.com/mfilipelino/11240714#file-paintopengl-c
	int dy = abs(r.p2.y - r.p1.y); //Diferença entre os pontos y2 e y1
	int dx = abs(r.p2.x - r.p1.x); //Diferença entre os pontos x2 e x1
	int sx, sy;					   //Variaveis que serão utilizadas para armazenar o sinal de x e y
	int i = r.p1.y;
	int j = r.p1.x;
	if (r.p1.x < r.p2.x) //Determinar os sinais de x e y
	{
		sx = 1;
	}
	else
	{
		sx = -1;
	}
	if (r.p1.y < r.p2.y)
	{
		sy = 1;
	}
	else
	{
		sy = -1;
	} //fim da determinação de sinais
	int erro;
	int erroTemp;
	if (dx > dy) // Definição do erro inicial baseado na maior diferença
	{
		erro = dx / 2;
	}
	else
	{
		erro = (-dy) / 2;
	}
	while (true)
	{
		p[i][j] = color(p[i][j], 0, 0, 0);
		if ((i == r.p2.y) && (j == r.p2.x)) // Testa se chegou ao ponto final da reta
		{
			break;
		}
		erroTemp = erro;
		if (erroTemp > -dx)
		{
			erro -= dy;
			j += sx;
		}
		if (erroTemp < dy)
		{
			erro += dx;
			i += sy;
		}
	}
}

void save(pixel **p, char n[50])
{
	FILE *fp = fopen(n, "w");
	if (fp == NULL)
	{
		printf("Erro na criação do arquivo");
	}
	else
	{
		fprintf(fp, "P3\n%d %d\n255\n", dimx, dimy);
		for (int j = 0; j < dimy; j++)
		{
			for (int i = 0; i < dimx; i++)
			{
				if (i != dimx - 1)
				{
					fprintf(fp, "%d %d %d ", p[i][j].red, p[i][j].green, p[i][j].blue);
				}
				else
				{
					fprintf(fp, "%d %d %d", p[i][j].red, p[i][j].green, p[i][j].blue);
				}
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
}

void polygon(pixel **p, int l, int x[l], int y[l])
{
	ponto p_ant;
	ponto p_atual;
	if ((x[0] != x[l]) && (y[0] != y[l]))
	{
		printf("Poligono inválido");
	}
	else
	{
		int i = 0;
		if (l > 0)
		{
			p_ant.x = x[i];
			p_ant.y = y[i];
			i++;
			l = l - 1;
			reta *r;
			r = malloc(l * sizeof(int));
			do
			{
				p_atual.x = x[i];
				p_atual.y = y[i];
				r[i].p1.x = p_ant.x;
				r[i].p1.y = p_ant.y;
				r[i].p2.x = p_atual.x;
				r[i].p2.y = p_atual.y;

				linha(p, r[i]);

				i++;
				l = l - 1;
				p_ant.x = p_atual.x;
				p_ant.y = p_atual.y;
			} while (l > 0);
			free(r);
		}
	}
}

void clear(pixel **p, unsigned short r, unsigned short g, unsigned short b)
{ //Limpa a imagem setando todos os pixels para uma cor especificada
	for (int j = 0; j < dimy; j++)
	{
		for (int i = 0; i < dimx; i++)
		{
			p[i][j] = color(p[i][j], r, g, b);
		}
	}
}

void circulo(pixel **p, ponto c, int r)
{ // https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
	//Função criada com algoritimo de Bresenham, através dos conhecimentos do pdf disponibilizados pelo professor juntamente com o link adicionado acima
	int xc, yc;
	xc = c.x;
	yc = c.y;
	int x = 0;
	int y = r;
	int d = 1 - r;
	p[xc + x][yc + y] = color(p[xc + x][yc + y], 0, 0, 0);
	p[xc - x][yc + y] = color(p[xc - x][yc + y], 0, 0, 0);
	p[xc + x][yc - y] = color(p[xc + x][yc - y], 0, 0, 0);
	p[xc - x][yc - y] = color(p[xc - x][yc - y], 0, 0, 0);
	p[xc + y][yc + x] = color(p[xc + y][yc + x], 0, 0, 0);
	p[xc - y][yc + x] = color(p[xc - y][yc + x], 0, 0, 0);
	p[xc + y][yc - x] = color(p[xc + y][yc - x], 0, 0, 0);
	p[xc - y][yc - x] = color(p[xc - y][yc - x], 0, 0, 0);
	while (x <= y)
	{
		x++;
		if (d < 0)
		{
			d = d + 2 * x + 1;
		}
		else
		{
			y--;
			d = d + 2 * (x - y) + 1;
		}
		p[xc + x][yc + y] = color(p[xc + x][yc + y], 0, 0, 0);
		p[xc - x][yc + y] = color(p[xc - x][yc + y], 0, 0, 0);
		p[xc + x][yc - y] = color(p[xc + x][yc - y], 0, 0, 0);
		p[xc - x][yc - y] = color(p[xc - x][yc - y], 0, 0, 0);
		p[xc + y][yc + x] = color(p[xc + y][yc + x], 0, 0, 0);
		p[xc - y][yc + x] = color(p[xc - y][yc + x], 0, 0, 0);
		p[xc + y][yc - x] = color(p[xc + y][yc - x], 0, 0, 0);
		p[xc - y][yc - x] = color(p[xc - y][yc - x], 0, 0, 0);
	}
}

void fill2(pixel **p, int x, int y, pixel cor, pixel borda)
{ //https://www.geeksforgeeks.org/boundary-fill-algorithm/

	if ((p[x][y].red == borda.red) &&
		(p[x][y].green == borda.green) &&
		(p[x][y].blue == borda.blue))
	{
		p[x][y] = color(p[x][y], cor.red, cor.green, cor.blue);
		if (x + 1 < dimx)
			fill2(p, x + 1, y, cor, borda);
		if (x - 1 >= 0)
			fill2(p, x - 1, y, cor, borda);
		if (y + 1 < dimy)
			fill2(p, x, y + 1, cor, borda);
		if (y - 1 >= 0)
			fill2(p, x, y - 1, cor, borda);
	}
}
void fill(pixel **p, int x, int y, pixel cor)
{
	pixel borda;
	borda.red = p[x][y].red;
	borda.blue = p[x][y].blue;
	borda.green = p[x][y].green;
	fill2(p, x, y, cor, borda);
}

void rect(pixel **p, int y, int x, int L, int A)
{ //FUNÇÃO PARA DESENHAR RETÂNGULOS

	reta r;
	for (int i = 1; i <= 4; i++)
	{
		if (i == 1 || i == 2)
		{
			r.p1.x = x;
			r.p1.y = y;
			r.p2.x = (x + L);
			r.p2.y = y;
			linha(p, r);
			if (i == 1)
			{
				y = y + A;
			}
			else
			{
				y = y - A;
			}
		}
		else
		{
			r.p1.x = x;
			r.p1.y = y;
			r.p2.x = x;
			r.p2.y = (y + A);
			linha(p, r);
			x = x + L;
		}
	}
}

int contar_spec(char n[50])
{ //FUNÇÃO QUE CONTA A QUANTIDADE DE LINHAS DO ARQUIVO
	int linhas = 0;
	char c, f = '\n';
	FILE *arq = fopen(n, "r");
	if (arq == NULL)
	{
		printf("Erro na abertura do arquivo");
	}
	else
	{
		while (fread(&c, sizeof(char), 1, arq))
		{
			if (c == f)
			{
				linhas++;
			}
		}
		fclose(arq);
	}

	return linhas;
}

t_tipos tam_tip(char n[50])
{ //FUNÇÃO QUE CONTA A QUANTIDADE DE TIPOS DO ARQUIVO DE ESPECIFICAÇÃO
	t_tipos a;
	a.color_t = 0;
	a.line_t = 0;
	a.polygon_t = 0;
	a.circle_t = 0;
	a.fill_t = 0;
	a.rect_t = 0;
	int i = 0, j = 0, t = 0;
	char linha[50];
	char l_aux[50];
	char comparador[4];
	FILE *arq = fopen(n, "r");
	if (arq == NULL)
	{
		printf("Erro na abertura do arquivo");
	}
	else
	{
		for (i = 0; i < (contar_spec(n)); i++)
		{
			fgets(linha, 50, arq);
			strcpy(l_aux, linha);
			memcpy(comparador, &linha[0], 4);
			comparador[4] = '\0';
			if (strcmp(comparador, "colo") == 0)
			{
				a.color_t++;
			}
			else if (strcmp(comparador, "line") == 0)
			{
				a.line_t++;
			}
			else if (strcmp(comparador, "poly") == 0)
			{
				a.polygon_t++;
			}
			else if (strcmp(comparador, "circ") == 0)
			{
				a.circle_t++;
			}
			else if (strcmp(comparador, "fill") == 0)
			{
				a.fill_t++;
			}
			else if (strcmp(comparador, "rect") == 0)
			{
				a.rect_t++;
			}
		}
		fclose(arq);
	}
	return a;
}

espec ler_spc(char n[50], char tipo[10])
{ //FUNÇÃO PARA LER O ARQUIVO DE ESPECIFICAÇÃO
	espec a;
	t_tipos tam = tam_tip(n);
	int i = 0, j = 0, t = 0;
	char linha[50];
	char l_aux[50];
	char comparador[4];
	char save_aux[50];
	FILE *arq = fopen(n, "r");
	FILE *aux = fopen("aux.txt", "w");
	if (aux == NULL)
	{
		printf("Erro na abertura do arquivo");
	}
	if (arq == NULL)
	{
		printf("Erro na abertura do arquivo");
	}
	else
	{
		if (strcmp(tipo, "color") == 0)
		{
			for (i = 0; i < (contar_spec(n)); i++)
			{
				fgets(linha, 50, arq);
				strcpy(l_aux, linha);
				memcpy(comparador, &linha[0], 4);
				comparador[4] = '\0';
				if (strcmp(comparador, "colo") == 0)
				{
					fputs(l_aux, aux);
				}
			}

			fclose(aux);
			FILE *aux = fopen("aux.txt", "r");
			for (i = 0; i < tam.color_t; i++)
			{
				fscanf(aux, "color %d %d %d\n", &a.color[i][0], &a.color[i][1], &a.color[i][2]);
			}
		}
		else if (strcmp(tipo, "line") == 0)
		{
			for (i = 0; i < (contar_spec(n)); i++)
			{
				fgets(linha, 50, arq);
				strcpy(l_aux, linha);
				memcpy(comparador, &linha[0], 4);
				comparador[4] = '\0';
				if (strcmp(comparador, "line") == 0)
				{
					fputs(l_aux, aux);
				}
			}
			fclose(aux);
			FILE *aux = fopen("aux.txt", "r");
			for (i = 0; i < tam.line_t; i++)
			{
				fscanf(aux, "line %d %d %d %d\n", &a.line[i][0], &a.line[i][1], &a.line[i][2], &a.line[i][3]);
			}
		}
		else if (strcmp(tipo, "polygon") == 0)
		{
			for (i = 0; i < (contar_spec(n)); i++)
			{
				fgets(linha, 50, arq);
				strcpy(l_aux, linha);
				memcpy(comparador, &linha[0], 4);
				comparador[4] = '\0';
				if (strcmp(comparador, "poly") == 0)
				{
					fputs(l_aux, aux);
				}
			}
			fclose(aux);
			FILE *aux = fopen("aux.txt", "r");
			for (i = 0; i < tam.polygon_t; i++)
			{
				fscanf(aux, "polygon %d %d %d %d %d %d %d\n", &a.polygon[i][0], &a.polygon[i][1], &a.polygon[i][2], &a.polygon[i][3], &a.polygon[i][4], &a.polygon[i][5], &a.polygon[i][6]);
			}
		}
		else if (strcmp(tipo, "circle") == 0)
		{
			for (i = 0; i < (contar_spec(n)); i++)
			{
				fgets(linha, 50, arq);
				strcpy(l_aux, linha);
				memcpy(comparador, &linha[0], 4);
				comparador[4] = '\0';
				if (strcmp(comparador, "circ") == 0)
				{
					fputs(l_aux, aux);
				}
			}
			fclose(aux);
			FILE *aux = fopen("aux.txt", "r");
			for (i = 0; i < tam.circle_t; i++)
			{
				fscanf(aux, "circle %d %d %d\n", &a.circle[i][0], &a.circle[i][1], &a.circle[i][2]);
			}
		}
		else if (strcmp(tipo, "fill") == 0)
		{
			for (i = 0; i < (contar_spec(n)); i++)
			{
				fgets(linha, 50, arq);
				strcpy(l_aux, linha);
				memcpy(comparador, &linha[0], 4);
				comparador[4] = '\0';
				if (strcmp(comparador, "fill") == 0)
				{
					fputs(l_aux, aux);
				}
			}
			fclose(aux);
			FILE *aux = fopen("aux.txt", "r");
			for (i = 0; i < tam.fill_t; i++)
			{
				fscanf(aux, "fill %d %d\n", &a.fill[i][0], &a.fill[i][1]);
			}
		}
		else if (strcmp(tipo, "rect") == 0)
		{
			for (i = 0; i < (contar_spec(n)); i++)
			{
				fgets(linha, 50, arq);
				strcpy(l_aux, linha);
				memcpy(comparador, &linha[0], 4);
				comparador[4] = '\0';
				if (strcmp(comparador, "rect") == 0)
				{
					fputs(l_aux, aux);
				}
			}
			fclose(aux);
			FILE *aux = fopen("aux.txt", "r");
			for (i = 0; i < tam.rect_t; i++)
			{
				fscanf(aux, "rect %d %d %d %d\n", &a.rect[i][0], &a.rect[i][1], &a.rect[i][2], &a.rect[i][3]);
			}
		}
		else if (strcmp(tipo, "image") == 0)
		{
			for (i = 0; i < (contar_spec(n)); i++)
			{
				fgets(linha, 50, arq);
				strcpy(l_aux, linha);
				memcpy(comparador, &linha[0], 4);
				comparador[4] = '\0';
				if (strcmp(comparador, "imag") == 0)
				{
					fputs(l_aux, aux);
				}
			}
			fclose(aux);
			FILE *aux = fopen("aux.txt", "r");
			fscanf(aux, "image %d %d\n", &a.image[0], &a.image[1]);
		}
		else if (strcmp(tipo, "clear") == 0)
		{
			for (i = 0; i < (contar_spec(n)); i++)
			{
				fgets(linha, 50, arq);
				strcpy(l_aux, linha);
				memcpy(comparador, &linha[0], 4);
				comparador[4] = '\0';
				if (strcmp(comparador, "clea") == 0)
				{
					fputs(l_aux, aux);
				}
			}
			fclose(aux);
			FILE *aux = fopen("aux.txt", "r");
			fscanf(aux, "clear %d %d %d\n", &a.clear[0], &a.clear[1], &a.clear[2]);
		}
		else if (strcmp(tipo, "save") == 0)
		{
			for (i = 0; i < (contar_spec(n)); i++)
			{
				fgets(linha, 50, arq);
				strcpy(l_aux, linha);
				memcpy(comparador, &linha[0], 4);
				comparador[4] = '\0';
				if (strcmp(comparador, "save") == 0)
				{
					fputs(l_aux, aux);
				}
			}
			fclose(aux);
			FILE *aux = fopen("aux.txt", "r");
			fgets(linha, 50, aux);
			for (i = 0; i < (strlen(linha) - 6); i++)
			{
				save_aux[i] = linha[(i + 5)];
                j=i;
			}
			save_aux[j+1] = '\0';
            j=0;
			strcpy(a.save, save_aux);
		}
	}
	fclose(aux);
	fclose(arq);
	return a;
}

espec ler_tudo(char n[50])
{
	espec a;
	a = ler_spc(n, "color");
	a = ler_spc(n, "line");
	a = ler_spc(n, "polygon");
	a = ler_spc(n, "circle");
	a = ler_spc(n, "fill");
	a = ler_spc(n, "rect");
	a = ler_spc(n, "image");
	a = ler_spc(n, "clear");
	a = ler_spc(n, "save");
	return a;
}
void chamar_tudo(pixel **p, char arquivo[50])
{
    espec img;
    t_tipos t_tip;
    t_tip = tam_tip(arquivo);
    img = ler_tudo(arquivo);
    imagem(img.save, img.image[0], img.image[1]);
    p = abrir_arquivo(img.save);
    if(t_tip.rect_t>0)
    {
        for(int i=0; i<t_tip.rect_t; i++)
        {                
            rect(p, img.rect[i][0], img.rect[i][1], img.rect[i][2], img.rect[i][3]);
        }
    }
    save(p, img.save);
    

}



#endif
