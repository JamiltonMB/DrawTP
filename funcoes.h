#ifndef FUNCOES_H
#define FUNCOES_H
#include "structs.h"

int dimx, dimy;//! Variavéis para armazenar o tamanho da imagem em edição durante a execução do programa.

pixel **allocar(int L, int C); //! FUNÇÃO DE ALOCAÇÃO DINÂMICA DE MÉMORIA: recebe dois inteiros L e C, que serão usados como referência para a alocação dinâmica de memória em uma matriz.

pixel color(pixel p, unsigned short r, unsigned short g, unsigned short b); //! Recebe um pixel e 3 valores(RGB 0-255) e retorna o pixel recebico com a nova cor passada.

pixel **imagem(int x, int y); //! Cria uma nova "imagem"(array bidimensional), com largura e altura especificadas(x,y).

pixel **abrir_arquivo(char w[50]); //! Funçao que lê e constroi o array pixel ** de acordo com o arquivo .txt: Recebe como parâmetor uma srting com o nome do arquivo para abrir e retorna o array pixel **p;

void linha(pixel **p, reta r); //! Função de desenhos de linhas, recebe duas structs como argumento, pixel e reta, a primeira armazena o vertor de desenho da imagem e a segunda armazena quatro inteiros, sendo que cada par de inteiro repressenta uma posição em pixel.

void save(pixel **p);//! FUNÇÃO SAVE: Recebe como paramâmetro uma struct do tipo pixel **, e uma string com o nome do arquivo da imagem. Os dados da matriz de pixel são armazenados do arquivo informado.

void polygon(pixel **p, int l, int x[l], int y[l]); //! Função de Desenho de polígonos, recebe uma struct pixel, um inteiro l e dois vetores de inteiro x e y com tamanho l, o inteiro l armaneza a quantidade de pontos do polígono e os vetores de inteiro x e y armazem as posições em pixel desses pontos.

void clear(pixel **p, unsigned short r, unsigned short g, unsigned short b); //! A função clear recebe três inteiros que serão usados para setar a cor de todos os pixels da imagem, limpando a imagem.

void circulo(pixel **p, ponto c, int r);//! Função criada com algoritimo de Bresenham, através dos conhecimentos do pdf disponibilizados pelo professor juntamente com o link adicionado acima. Recebe uma struct do tipo pixel, outra do tipo ponto e um inteiro. O pixel armazena todos os pixel da imagem, o ponto armazena a localização do pixel do centro do círculo e o inteiro r armazena o tamanho do raio do círculo.

void fill(pixel **p, int x, int y, pixel cor); /* Recebe uma strutct do tipo pixel, dois inteiros x e y para determinar o ponto inicial do preenchimento, e dois pixels(struct que armazena os valores RGB) para determinar a cor que deve ser pintada além de ter um controle para o fim do algoritimo de referencia https://www.geeksforgeeks.org/boundary-fill-algorithm/ . */

void fill2(pixel **p, int x, int y, pixel core, pixel borda);//! Função auxiliar da fill que inicializa os valores de pixel borda.

void react(pixel **p, int x, int y, int A, int L); /* Função para desenhar retângulos: Passando os parâmetros x,y(um ponto na imagem) A:altura , L:largura do retângulo. 
OBS:O retângulo será desenhado da esquerda para a direita e de cima para baixo a partir do ponto digitado. */

int contar_spec(char n[50]); //! Função que conta a quantidade de linhas do arquivo: recebe o nome do arquivo e retorna um inteiro com a quantidade de linhas no arquivo.

void ler_save(char n[50], char i_nome[50]);//! Função para ler o nome de um arquivo de imagem .ppm e armazena-lo em uma string para manipulação no programa.

void ler_spc(pixel **p, char n[50]); //! Função para ler o arquivo de especificação e gerar a imagem tal qual escrita no arquivo.

espec ler_image(char spc_n[50], char img_n[50]);//! Função que armazena o tamanho da imagem lido no arquivo de especificação.

#endif

