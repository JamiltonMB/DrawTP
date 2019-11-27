#ifndef FUNCOES_H
#define FUNCOES_H
#include "structs.h"

int dimx, dimy;

pixel **allocar(int L, int C); // FUNÇÃO DE ALOCAÇÃO DINÂMICA DE MÉMORIA: recebe dois inteiros L e C, que serão usados como referência para a alocação dinâmica de memória em uma matriz.

pixel color(pixel p, unsigned short r, unsigned short g, unsigned short b); //Armanzea o valor da cor no padrão RGB.

pixel **imagem(int x, int y); //Cria uma nova "imagem", com largura e altura especificadas

pixel **abrir_arquivo(char w[50]); //FUNÇÃO DE LEITURA DO ARQUIVO DE ESPECIFICAÇÃO: Recebe como parâmetor uma srting com o nome do arquivo, a função abre o arquivo e armazena seu conteúdo na struct pixel **p;

void linha(pixel **p, reta r); // Função de desenhos de linhas, recebe duas structs como argumento, pixel e reta, a primeira armazena o vertor de desenho da imagem e a segunda armazena quatro inteiros, sendo que cada par de inteiro repressenta uma posição em pixel.

void save(pixel **p);//FUNÇÃO SAVE: Recebe como paramâmetro uma struct do tipo pixel **, e uma string com o nome do arquivo da imagem. Os dados da matriz de pixel são armazenados do arquivo informado.

void polygon(pixel **p, int l, int x[l], int y[l]); //Função de Desenho de polígonos, recebe uma struct pixel, um inteiro l e dois vetores de inteiro x e y com tamanho l, o inteiro l armaneza a quantidade de pontos do polígono e os vetores de inteiro x e y armazem as posições em pixel desses pontos.

void clear(pixel **p, unsigned short r, unsigned short g, unsigned short b); //A função clear recebe três inteiros que serão usados para setar a cor de todos os pixels da imagem, limpando a imagem.

void circulo(pixel **p, ponto c, int r);//Função criada com algoritimo de Bresenham, através dos conhecimentos do pdf disponibilizados pelo professor juntamente com o link adicionado acima. Recebe uma struct do tipo pixel, outra do tipo ponto e um inteiro. O pixel armazena todos os pixel da imagem, o ponto armazena a localização do pixel do centro do círculo e o inteiro r armazena o tamanho do raio do círculo.

void fill(pixel **p, int x, int y, pixel cor, pixel borda); //Recebe uma strutct do tipo pixel, dois inteiros x e y e outra struct do tipo core.

void react(pixel **p, int x, int y, int A, int L); //FUNÇÃO PARA DESENHAR RETÂNGULOS

int contar_spec(char n[50]); //FUNÇÃO QUE CONTA A QUANTIDADE DE linhas DO ARQUIVO: recebe o nome do arquivo e retorna 

void ler_save(char n[50], char i_nome[50]);//FUNÇÃO QUE LER O NOME DO ARQUIVO PPM E ARMAZENA EM UMA STRING

void ler_spc(pixel **p, char n[50]); //FUNÇÃO PARA LER O ARQUIVO DE ESPECIFICAÇÃO

espec ler_image(char spc_n[50], char img_n[50]);//Função que armazena o tamanho da imagem lido no arquivo de especificação

#endif

