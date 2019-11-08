#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"

int main(){
    int x,y;
    pixel **p;
    reta r;
    printf("Digite o tamanho da imagem:\n");
    scanf("%d",&x);
    scanf("%d",&y);
    p=image(x,y);
    printf("Digite o x1/y1:\n");
    scanf("%d",&r.p1.x);
    scanf("%d",&r.p1.y);
    printf("Digite o x2/y2:\n");
    scanf("%d",&r.p2.x);
    scanf("%d",&r.p2.y);
    linha(p,r);
    save(p);
return 0;
}
