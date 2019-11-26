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

t_tipos tam_tip(char n[50])
{ //FUNÇÃO QUE CONTA A QUANTIDADE DE TIPOS DO ARQUIVO DE ESPECIFICAÇÃO
	t_tipos a;
	a.color_t = 0;
	a.line_t = 0;
	a.polygon_t = 0;
	a.circle_t = 0;
	a.fill_t = 0;
	a.rect_t = 0;
	int i = 0;
	char linha2[50];
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
			fgets(linha2, 50, arq);
			strcpy(l_aux, linha2);
			memcpy(comparador, &linha2[0], 4);
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

espec ler_save(char n[50])
{
	espec a;
	FILE *arq = fopen(n, "r");
	FILE *aux = fopen("aux.txt", "w");
	char linha2[50];
	char l_aux[50];
	char comparador[4];
	char save_aux[50];
	int i, j;
	for (i = 0; i < (contar_spec(n)); i++)
	{
		fgets(linha2, 50, arq);
		strcpy(l_aux, linha2);
		memcpy(comparador, &linha2[0], 4);
		comparador[4] = '\0';
		if (strcmp(comparador, "save") == 0)
		{
			fputs(l_aux, aux);
		}
	}
	fclose(aux);
	FILE *aux1 = fopen("aux.txt", "r");
	fgets(linha2, 50, aux1);
	for (i = 0; i < (strlen(linha2) - 6); i++)
	{
		save_aux[i] = linha2[(i + 5)];
		j = i;
	}
	save_aux[j + 1] = '\0';
	j = 0;
	strcpy(a.save, save_aux);
	fclose(aux1);
	fclose(arq);
	return a;
}

void ler_spc(pixel **p, char n[50])
{ //FUNÇÃO PARA LER O ARQUIVO DE ESPECIFICAÇÃO

	espec a;
	a = ler_save(n);
	//t_tipos tam = tam_tip(n);
	int i = 0;
	char linha2[50];
	char l_aux[50];
	char comparador[4];
	char save_aux[50];
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
				linha2(p, r);
			}
			else if (strcmp(comparador, "poly") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "polygon %d %d %d %d %d %d %d\n", &a.polygon[0], &a.polygon[1], &a.polygon[2], &a.polygon[3], &a.polygon[4], &a.polygon[5], &a.polygon[6]); // só funciona pra 3 pontos, rever depois
				fclose(aux);
				aux = fopen("aux.txt", "w");
				polygon(p, int l, int x[l], int y[l]);
			}
			else if (strcmp(comparador, "circ") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "circle %d %d %d\n", &a.circle[[0], &a.circle[1], &a.circle[2]);
				fclose(aux);
				aux = fopen("aux.txt", "w");
				ponto c;
				c.x=a.circle[[0];
                c.y=a.circle[[1];
                circulo(p, c, a.circle[2]);
			}
			else if (strcmp(comparador, "fill") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "fill %d %d\n", &a.fill[0], &a.fill[1]);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "w");
				pixel cor;
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
				FILE *aux = fopen("aux.txt", "w");
				pixel cor;
				//falta implementar a função color da forma correta
				rect(p, a.rect[1], a.rect[0], a.rect[3], a.rect[2]);
			}
			else if (strcmp(comparador, "imag") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "image %d %d\n", &a.image[0], &a.image[1]);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "w");
				imagem(char n[50], a.image[0], a.image[1]);
			}
			else if (strcmp(comparador, "clea") == 0)
			{
				fputs(l_aux, aux);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "r");
				fscanf(aux, "clear %d %d %d\n", &a.clear[0], &a.clear[1], &a.clear[2]);
				fclose(aux);
				FILE *aux = fopen("aux.txt", "w");
				clear(p, a.clear[0], a.clear[1], a.clear[2]);
			}
		}
	}