#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct ponto{ //Struct para armazenar as posições x e y de um ponto

int x , y;

}ponto;

typedef struct reta{ //Struct para armazenar 2 ou mais pontos para formarem uma reta

ponto p1;
ponto p2;

}reta;

typedef struct pixel{ //Struct para armazenar as cores no canvas
     unsigned short red,green,blue;
} pixel;

#endif

