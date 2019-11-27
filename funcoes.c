#ifndef FUNCOES_C
#define FUNCOES_C
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dimx;
int dimy;
pixel cor;

pixel **allocar(int L, int C)
{ // FUNÇÃO DE ALOCAÇÃO DINÂMICA DE MÉMORIA: recebe dois inteiros L e C, que serão usados como referência para a alocação dinâmica de memória em uma matriz.
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
{ //FUNÇÃO DE CRIAÇÃO DE IMAGENS: Cria uma nova "imagem", com largura(inteiro x) e altura (inteiro y) especificadas.
	FILE *fp = fopen(n, "w");
	dimx = x;
	dimy = y;
	pixel **p = allocar(dimx, dimy);
	cor.red = 255;
	cor.green = 255;
	cor.blue = 255;
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
				p[i][j] = color(p[i][j], cor.red, cor.green, cor.blue);
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
{ //FUNÇÃO DE LEITURA DO ARQUIVO DE ESPECIFICAÇÃO: Recebe como parâmetor uma srting com o nome do arquivo, a função abre o arquivo e armazena seu conteúdo na struct pixel **p;
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

void linha(pixel **p, reta r)	  // Função de desenhos de linhas
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
		p[i][j] = color(p[i][j], cor.red, cor.green, cor.blue); //  ATENÇÃO: >>>> MODIFIQUEI ESSES VALORES PARA TESTES
		if ((i == r.p2.y) && (j == r.p2.x))						// Testa se chegou ao ponto final da reta
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

void save(pixel **p, char n[50]) //FUNÇÃO SAVE: Recebe como paramâmetro uma struct do tipo pixel **, e uma string com o nome do arquivo da imagem. Os dados da matriz de pixel são armazenados do arquivo informado.
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
	p[xc + x][yc + y] = color(p[xc + x][yc + y], cor.red, cor.green, cor.blue);
	p[xc - x][yc + y] = color(p[xc - x][yc + y], cor.red, cor.green, cor.blue);
	p[xc + x][yc - y] = color(p[xc + x][yc - y], cor.red, cor.green, cor.blue);
	p[xc - x][yc - y] = color(p[xc - x][yc - y], cor.red, cor.green, cor.blue);
	p[xc + y][yc + x] = color(p[xc + y][yc + x], cor.red, cor.green, cor.blue);
	p[xc - y][yc + x] = color(p[xc - y][yc + x], cor.red, cor.green, cor.blue);
	p[xc + y][yc - x] = color(p[xc + y][yc - x], cor.red, cor.green, cor.blue);
	p[xc - y][yc - x] = color(p[xc - y][yc - x], cor.red, cor.green, cor.blue);
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
		p[xc + x][yc + y] = color(p[xc + x][yc + y], cor.red, cor.green, cor.blue);
		p[xc - x][yc + y] = color(p[xc - x][yc + y], cor.red, cor.green, cor.blue);
		p[xc + x][yc - y] = color(p[xc + x][yc - y], cor.red, cor.green, cor.blue);
		p[xc - x][yc - y] = color(p[xc - x][yc - y], cor.red, cor.green, cor.blue);
		p[xc + y][yc + x] = color(p[xc + y][yc + x], cor.red, cor.green, cor.blue);
		p[xc - y][yc + x] = color(p[xc - y][yc + x], cor.red, cor.green, cor.blue);
		p[xc + y][yc - x] = color(p[xc + y][yc - x], cor.red, cor.green, cor.blue);
		p[xc - y][yc - x] = color(p[xc - y][yc - x], cor.red, cor.green, cor.blue);
	}
}

void fill2(pixel **p, int x, int y, pixel core, pixel borda)
{ //https://www.geeksforgeeks.org/boundary-fill-algorithm/

	if ((p[x][y].red == borda.red) &&
		(p[x][y].green == borda.green) &&
		(p[x][y].blue == borda.blue))
	{
		p[x][y] = color(p[x][y], core.red, core.green, core.blue);
		if (x + 1 < dimx)
			fill2(p, x + 1, y, core, borda);
		if (x - 1 >= 0)
			fill2(p, x - 1, y, core, borda);
		if (y + 1 < dimy)
			fill2(p, x, y + 1, core, borda);
		if (y - 1 >= 0)
			fill2(p, x, y - 1, core, borda);
	}
}
void fill(pixel **p, int x, int y, pixel core)
{
	pixel borda;
	borda.red = p[x][y].red;
	borda.blue = p[x][y].blue;
	borda.green = p[x][y].green;
	fill2(p, x, y, core, borda);
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
{ //FUNÇÃO QUE CONTA A QUANTIDADE DE linha2S DO ARQUIVO
	int linha2s = 0;
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
				linha2s++;
			}
		}
		fclose(arq);
	}

	return linha2s;
}

void ler_save(char n[50], char i_nome[50])
{ //FUNÇÃO QUE LER O NOME DO ARQUIVO PPM E ARMAZENA EM UMA STRING
	int i = 0, j = 0;
	char linha[50];
	char l_aux[50];
	char comparador[4];
	char save_img[50];
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
			if (strcmp(comparador, "save") == 0) //{fputs(l_aux, aux);}
			{
				for (i = 0; i < (strlen(l_aux) - 6); i++)
				{
					save_img[i] = linha[(i + 5)];
					j = i;
				}
				save_img[j + 1] = '\0';
				strcpy(i_nome, save_img);
			}
		}
		fclose(arq);
	}
}

espec ler_image(char spc_n[50], char img_n[50])
{ // FUNÇÃO QUE LER O TAMANHO DA IMAGEM E ARMAENZA EM UMA STRUCT
	espec a;
	int i;
	FILE *arq = fopen(spc_n, "r");
	for (i = 0; i < (contar_spec(spc_n)); i++)
	{
		fscanf(arq, "image %d %d\n", &a.image[0], &a.image[1]);
	}
	fclose(arq);
	imagem(img_n, a.image[0], a.image[1]);
	strcpy(a.save, img_n);
	return a;
}

void ler_spc(pixel **p, char n[50])
{ //FUNÇÃO PARA LER O ARQUIVO DE ESPECIFICAÇÃO
	espec a;
	ler_save(n, a.save);
	a = ler_image(n, a.save);
	//t_tipos tam = tam_tip(n);

	int i = 0;
	char linha2[50];
	char l_aux[50];
	char comparador[4];
	FILE *arq = fopen(n, "r");
	FILE *aux = fopen("aux.txt", "w");
	if (aux == NULL)
	{
		printf("Erro na abertura do arquivo");
		return;
	}
	if (arq == NULL)
	{
		printf("Erro na abertura do arquivo");
		return;
	}
	else
	{
		p = abrir_arquivo(a.save);
		for (i = 0; i < (contar_spec(n)); i++)
		{
			fgets(linha2, 50, arq);
			strcpy(l_aux, linha2);
			memcpy(comparador, &linha2[0], 4);
			comparador[4] = '\0';

			if (strcmp(comparador, "colo") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "color %d %d %d\n", &a.color[0], &a.color[1], &a.color[2]);
				fclose(aux);
				aux = fopen("aux.txt", "w");
				cor = color(cor, a.color[0], a.color[1], a.color[2]);
			}
			else if (strcmp(comparador, "line") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "line %d %d %d %d\n", &a.line[0], &a.line[1], &a.line[2], &a.line[3]);
				fclose(aux);
				aux = fopen("aux.txt", "w");
				reta r;
				r.p1.x = a.line[0];
				r.p1.y = a.line[1];
				r.p2.x = a.line[2];
				r.p2.y = a.line[3];
				linha(p, r);
			}
			else if (strcmp(comparador, "poly") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				polygons a;
				fscanf(aux, "polygon %d ", &a.tam);
				for (int t = 0; t < a.tam; t++)
				{
					fscanf(aux, "%d ", &a.x[t]);
					if (t != a.tam - 1)
					{
						fscanf(aux, "%d ", &a.y[t]);
					}
					else
					{
						fscanf(aux, "%d", &a.y[t]);
					}
				}
				fscanf(aux, "\n");
				fclose(aux);
				aux = fopen("aux.txt", "w");
				polygon(p, a.tam, a.x, a.y);
			}
			else if (strcmp(comparador, "circ") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "circle %d %d %d\n", &a.circle[0], &a.circle[1], &a.circle[2]);
				fclose(aux);
				aux = fopen("aux.txt", "w");
				ponto c;
				c.x = a.circle[0];
				c.y = a.circle[1];
				circulo(p, c, a.circle[2]);
			}
			else if (strcmp(comparador, "fill") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "fill %d %d\n", &a.fill[0], &a.fill[1]);
				fclose(aux);
				aux = fopen("aux.txt", "w");
				//falta implementar a função color da forma correta
				fill(p, a.fill[0], a.fill[1], cor);
			}
			else if (strcmp(comparador, "rect") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "rect %d %d %d %d\n", &a.rect[0], &a.rect[1], &a.rect[2], &a.rect[3]);
				fclose(aux);
				aux = fopen("aux.txt", "w");
				//falta implementar a função color da forma correta
				rect(p, a.rect[0], a.rect[1], a.rect[3], a.rect[2]);
			}
			else if (strcmp(comparador, "clea") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "clear %d %d %d\n", &a.clear[0], &a.clear[1], &a.clear[2]);
				fclose(aux);
				aux = fopen("aux.txt", "w");
				clear(p, a.clear[0], a.clear[1], a.clear[2]);
			}
		}
		save(p, a.save);
	}
}
/*
void debugadora(pixel **p, char arquivo[50])//função para DEBUG
{
    char img_nome[50];
    ler_save(arquivo, img_nome);
    p = abrir_arquivo(img_nome);               
    rect(p, 0, 0, 100, 100);
    save(p, img_nome);  
}
*/
#endif
