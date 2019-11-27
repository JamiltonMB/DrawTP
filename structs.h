#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{ //Struct para armazenar as posições x e y de um ponto

    int x, y;

} ponto;

typedef struct
{ //Struct para armazenar 2 ou mais pontos para formarem uma reta

    ponto p1;
    ponto p2;

} reta;

typedef struct
{ //Struct para armazenar as cores
    unsigned short red, green, blue;
} pixel;

enum Bool
{
    false = 0,
    true = 1
};

typedef struct espec_s
{ //STRUCT PARA ARMAZENAR O ARQUIVO DE ESPECIFICAÇÃO
    int image[2], clear[3], color[3], line[4], polygon[7], circle[3], fill[2], rect[4];
    char save[50];
} espec;

#endif
