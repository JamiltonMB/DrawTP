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

#endif

