#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct{ //Struct para armazenar as posições x e y de um ponto

int x , y;

}ponto;

typedef struct{ //Struct para armazenar 2 ou mais pontos para formarem uma reta

ponto p1;
ponto p2;

}reta;

typedef struct{ //Struct para armazenar as cores
     unsigned short red,green,blue;
} pixel;

enum Bool
{
    false = 0,
    true = 1
};

typedef struct espec_s{   //STRUCT PARA ARMAZENAR O ARQUIVO DE ESPECIFICAÇÃO
int image[2], clear[3], color[50][3], line[50][4], polygon[50][7], circle[50][3], fill[50][2],rect[50][4];
char save[50];
}espec;

typedef struct t_tipos_s{
int color_t, line_t, polygon_t, circle_t, fill_t, rect_t;
}t_tipos;

#endif

