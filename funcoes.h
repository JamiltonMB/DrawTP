#ifndef FUNCOES_H
#define FUNCOES_H
#include "structs.h"

int dimx, dimy;

pixel **allocar(int L, int C);

pixel color(pixel p, unsigned short r, unsigned short g, unsigned short b);

pixel **imagem(int x, int y); //Cria uma nova "imagem", com largura e altura especificadas

pixel **abrir_arquivo(char w[50]); //função para letitura do arquivo

void linha(pixel **p, reta r); //https://gist.github.com/mfilipelino/11240714#file-paintopengl-c

void save(pixel **p);

void polygon(pixel **p, int l, int x[l], int y[l]);

void clear(pixel **p, unsigned short r, unsigned short g, unsigned short b); //Limpa a imagem setando todos os pixels para uma cor especificada

void circulo(pixel **p, ponto c, int r);

void fill(pixel **p, int x, int y, pixel cor, pixel borda); //https://www.geeksforgeeks.org/boundary-fill-algorithm/

void react(pixel **p, int x, int y, int A, int L); //FUNÇÃO PARA DESENHAR RETÂNGULOS

int contar_spec(char n[50]); //FUNÇÃO QUE CONTA A QUANTIDADE DE LINHAS DO ARQUIVO

void ler_spc(pixel **p, char n[50]); //FUNÇÃO PARA LER O ARQUIVO DE ESPECIFICAÇÃO

#endif
